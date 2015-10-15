/*
  I'm very sorry that I can't use java now because there's no toolchain here.
  However, I know java and am pretty familiar with it.
  So I translate the excersize into C++'s.
  Note that I will exploit the C++11 standard.
*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <cassert>

using namespace std;

/**
 * Represents a car trying to park in the parking garage.
 */
class _Car {
public:
    /**
     * @return The state in which the license plate was issued.
     */
    virtual string getLicensePlateState() = 0;

    /**
     * @return The license plate number of the car.
     */
    virtual string getLicensePlateNumber() = 0;
};

/*
  I don't use Space and Car class directly.
  Instead, I will wrap them with `shared_ptr` to mimic Java's handles.
*/
typedef shared_ptr<_Car> Car;

/**
 * Represents a space in the garage in which a car can park.
 */
class _Space {
public:
    /**
     * @return A unique identifier for the given space.
     */
    virtual int getID() = 0;

    /**
     * @return An integer representing the desirability of the space.
     *         Spaces with higher values are considered more desirable.
     */
    virtual int getDesirability() = 0;

    /**
     * @return true if the space is currently occupied with a car;
     *         false, otherwise. This returns the real world state of
     *         the Space.
     */
    virtual bool isOccupied() = 0;

    /**
     * @return the Car that is currently occupying the Space or null
     *         if no Car is currently present. This returns the real
     *         world state of the space.
     */
    virtual Car getOccupyingCar() = 0;
};

/*
  Like the case of Car.
 */
typedef shared_ptr<_Space> Space;

/**
 * An interface used to receive callbacks about changes in the status
 * of Spaces and cars in the garage. Implementers will receive notifications
 * whenever a space becomes occupied or unoccupied and whenever a car
 * leaves the garage.
 */
class GarageStatusListener {
public:
    /**
     * Invoked whenever a car parks in a space.
     * @param car The car parking in the space.
     * @param space The space being occupied.
     */
    virtual void onSpaceTaken(Car car, Space space) = 0;

    /**
     * Invoked whenever a car leaves a space.
     * @param car The car leaving the space.
     * @param space The space that the car left.
     */
    virtual void onSpaceFreed(Car car, Space space) = 0;

    /**
     * Invoked whenever a car leaves the garage.
     * @param car The car leaving the garage.
     */
    virtual void onGarageExit(Car car) = 0;
};

/**
 * The main app controlling the parking garage.
 */
class ParkingGarage {
public:
    /**
     * Registers the given garage status listener to receive notifications for
     * changes in the occupied status of a space.
     * @param assigner The GarageStatusListener responsible for issuing spaces.
     */

    /* Note!
       Renamed `register` to `registerListener`, cause it is a keyword of C++.
       */
    virtual void registerListener(GarageStatusListener& assigner) = 0;

    /**
     * @return the list of spaces in the parking garage. Note: This list may be
     * very large and take a long time to iterate through.
     */

    /* Note!
       Using `vector`, instead of Java's iterator.
     */
    virtual const vector<Space>& getSpaces() = 0;
};

class CompareSpace {
public:
    bool operator() (const Space& lhs, const Space& rhs) {
        return lhs->getDesirability() < rhs->getDesirability();
    }
};

/**
 * The SpaceAssigner is responsible for assigning a space for an incoming
 * car to park in. This is done by calling the assignSpace() API.
 *
 * The SpaceAssigner responds to changes in space availability by
 * implementing the GarageStatusListener interface.
 */
class SpaceAssigner : public GarageStatusListener {
#ifndef __TEST
private:
#else
public:
#endif

    // use heap to choose the most desirable space.
    typedef priority_queue<Space, vector<Space>, CompareSpace> SpaceHeap;

    SpaceHeap _space_pool;

    /*
      I used `unordered_map`, cause in most case it shows O(1) complexity and is more memory-efficient.
      However it tends to increase the worst case time complexity.
      If it matters, `map` will be a good alternative.
    */
    unordered_map<string, Space> _assigned_not_taken;

public:
    /**
     * Initiates the SpaceAssigner. This method is called only once per
     * app start-up.
     * @param garage The parking garage for which you are vending spaces.
     *
     * <<insert runtime and memory analysis here>>
     * 1. Time complexity analysis
     *  time to heapify = O(N) (for the STL's)
     *
     * 2. Space complexity analysis
     *  = O(N) (for internal vector container)
     */
    void initialize(ParkingGarage& garage) {
        // insert code here
        const auto& spaces = garage.getSpaces();
        _space_pool = SpaceHeap(spaces.begin(), spaces.end());
        garage.registerListener(*this);
    }

    /**
     * Assigns a space to an incoming car and returns that space.
     *
     * @param car The incoming car that needs a space.
     * @returns The space reserved for the incoming car.
     *
     * <<insert runtime and memory analysis here>>
     * 1. Time complexity analysis
     *   A pop operation of priory queue = O(log N)
     *   + an insertion of hash map = O(N) (worst case), O(1) (most cases)
     *   = O(N) (worst case), O(log N) (most cases)
     *  c.f. if I used `map`(RB-tree) instead of `unordered_map`, this is O(log N) in both cases.
     *
     * 2. Space complexity analysis
     *  priory queue = O(N)
     *  + unordered_map = O(N)
     *  = O(N)
     * c.f. same for `map`
     */
    Space assignSpace(Car car) {
        // insert code here
        if(_space_pool.empty())
            return {};

        auto space = _space_pool.top();
        _space_pool.pop();
        _assigned_not_taken[car->getLicensePlateNumber()] = space;
        return move(space);
    }

    /**
     * {@inheritDoc}
     *
     * <<insert runtime and memory analysis here>>
     * removal from hash map = O(N) (worst case), O(1) (most cases)
     */
    virtual void onSpaceTaken(Car car, Space space) override {
        // insert code here
        auto space_from_car = _assigned_not_taken.find(car->getLicensePlateNumber());
        assert(space_from_car != _assigned_not_taken.end());

        /*
          I have to admit that I didn't consider the case that drivers don't choose assigned spaces.
          However, I know the way to deal this case with some overhead of computation.
          Using `map` instead of `priority_queue` can erase random spaces from `_space_pool`,
          though it will increase time complexity of `SpaceAssigner::initialize()` to O(N logN).

          */
        assert(space_from_car->second->getID() == space->getID());

        // Now, the space becomes taken.
        _assigned_not_taken.erase(space_from_car);
    }

    /**
     * {@inheritDoc}
     *
     * <<insert runtime and memory analysis here>>
     * insertion into heap = O(log N) (in average and worst cases)
     */
    virtual void onSpaceFreed(Car car, Space space) override {
        // insert code here
        // Following assertion can't be tested cause there's no routine setting cars to spaces.
        // assert(space->getOccupyingCar()->getLicensePlateNumber() == car->getLicensePlateNumber());
        _space_pool.push(move(space));
    }

    /**
     * {@inheritDoc}
     *
     * <<insert runtime and memory analysis here>>
     * 1. Time complexity analysis
     *  search and removal from hash map = O(N) (worst case), O(1) (most cases)
     *  + a push into heap = O(log N)
     *  = O(N) (worst case), O(log N) (most cases)
     */
    void onGarageExit(Car car) override {
        // insert code here
        auto space = _assigned_not_taken.find(car->getLicensePlateNumber());
        if(space == _assigned_not_taken.end())
            return;

        // The driver didn't park in any space, we need to take the space of the car back.
        _space_pool.push(move(space->second));
        _assigned_not_taken.erase(space);
    }
};

// Tests here.
// Implemented some classes for testing, because C++ doesn't have anonymous class of Java.
// Use "Catch" for unit testing. (https://github.com/philsquared/Catch)
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

class MyCar
    : public _Car {
public:
    /**
     * @return The state in which the license plate was issued.
     */
    virtual string getLicensePlateState() override {
        // don't use this.
        return {};
    };

    /**
     * @return The license plate number of the car.
     */
    virtual string getLicensePlateNumber() override {
        return to_string(_plateNumber);
    }

private:
    static unsigned int _plateNumberSeed;
    unsigned int _plateNumber{_plateNumberSeed++};
};

unsigned int MyCar::_plateNumberSeed{0};

class MySpace
    : public _Space {
public:
    /**
     * @return A unique identifier for the given space.
     */
    virtual int getID() override {
        return _id;
    }

    /**
     * @return An integer representing the desirability of the space.
     *         Spaces with higher values are considered more desirable.
     */
    virtual int getDesirability() override {
        // using id for simplicity.
        return _id;
    }

    /**
     * @return true if the space is currently occupied with a car;
     *         false, otherwise. This returns the real world state of
     *         the Space.
     */
    virtual bool isOccupied() override {
        return static_cast<bool>(_car);
    }

    /**
     * @return the Car that is currently occupying the Space or null
     *         if no Car is currently present. This returns the real
     *         world state of the space.
     */
    virtual Car getOccupyingCar() override {
        return _car;
    }

private:
    static unsigned int _idSeed;
    unsigned int _id{_idSeed++};
    Car _car;
};

unsigned int MySpace::_idSeed{0};

class MyParkingGarage
    : public ParkingGarage {
public:
    MyParkingGarage(size_t n) {
        while(n--) {
            _spaces.emplace_back(new MySpace());
        }
    }

    /**
     * Registers the given garage status listener to receive notifications for
     * changes in the occupied status of a space.
     * @param assigner The GarageStatusListener responsible for issuing spaces.
     */

    /* Note!
       Renamed `register` to `registerListener`, cause it is a keyword of C++.
    */
    virtual void registerListener(GarageStatusListener& assigner) override {
    }

    /**
     * @return the list of spaces in the parking garage. Note: This list may be
     * very large and take a long time to iterate through.
     */

    /* Note!
       Using `vector`, instead of Java's iterator.
    */
    const vector<Space>& getSpaces() override {
        return _spaces;
    }

#ifndef __TEST
private:
#endif
    vector<Space> _spaces;
};

TEST_CASE("initializing") {
    MyParkingGarage garage(100);
    SpaceAssigner assigner;
    assigner.initialize(garage);
    REQUIRE(assigner._space_pool.size() == 100);
    REQUIRE(assigner._space_pool.size() == garage._spaces.size());
}

TEST_CASE("space full") {
    MyParkingGarage garage(100);
    SpaceAssigner assigner;
    assigner.initialize(garage);

    for(int i = 0; i < 110; ++i) {
        Car car{new MyCar()};
        auto space = assigner.assignSpace(car);
        if(i < 100)
            REQUIRE(static_cast<bool>(space));
        else
            REQUIRE(!static_cast<bool>(space));
    }
}

TEST_CASE("desceding desirability") {
    MyParkingGarage garage(100);
    SpaceAssigner assigner;
    assigner.initialize(garage);

    int d = 1000;
    for(int i = 0; i < 100; ++i) {
        Car car{new MyCar()};
        auto space = assigner.assignSpace(car);
        REQUIRE(d > space->getDesirability());
        d = space->getDesirability();
    }
}

TEST_CASE("testing normal drivers") {
    MyParkingGarage garage(100);
    SpaceAssigner assigner;
    assigner.initialize(garage);

    int d = 1000;
    for(int i = 0; i < 100; ++i) {
        Car car{new MyCar()};
        auto space = assigner.assignSpace(car);

        if(i % 2 == 0) {
            assigner.onSpaceTaken(car, space);
            assigner.onSpaceFreed(car, space);
            assigner.onGarageExit(car);
        }
    }
    REQUIRE(assigner._space_pool.size() == 50);
}

TEST_CASE("testing transient drivers") {
    MyParkingGarage garage(100);
    SpaceAssigner assigner;
    assigner.initialize(garage);

    int d = 1000;
    for(int i = 0; i < 100; ++i) {
        Car car{new MyCar()};
        auto space = assigner.assignSpace(car);

        if(i % 2 == 0) {
            assigner.onSpaceTaken(car, space);
            assigner.onSpaceFreed(car, space);
        }
        assigner.onGarageExit(car);
    }
    REQUIRE(assigner._space_pool.size() == 100);
}
