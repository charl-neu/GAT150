#pragma once
#include "../Math/Vector2.h"
#include "../Math/Math.h"
#include <cstdlib>
#include <random>

namespace viper::random {
    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    /// <summary>
	/// Sets the seed for the random number generator.
    /// </summary>
    /// <param name="value"> The seeds used to set to the rng. Same seed means same random result</param>
    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    /// <summary>
	/// Generates a random integer between min and max, inclusive.
    /// </summary>
    /// <param name="min"> the lowest int value that will be generated </param>
    /// <param name="max"> the highest int value that will be generated </param>
    /// <returns></returns>
    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    /// <summary>
	/// Generates a random integer between 0 and some number minus one, inclusive.
    /// </summary>
    /// <param name="max"> The highest int value that will be generated </param>
    /// <returns></returns>
    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    /// <summary>
	/// Generates a random integer between 0 and the maximum value of int, inclusive.
    /// </summary>
    /// <returns></returns>
    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    /// <summary>
	/// Generates a random floating-point number between min and max, inclusive.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="min"> the lowest floating point number to be generated </param>
    /// <param name="max"> the highest floating point number to be generated</param>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    /// <summary>
	/// Generates a random floating-point number between 0 and max, inclusive.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="max"> the highest floating point number to be generated</param>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    /// <summary>
	/// Generates a random floating-point number between 0 and 1, inclusive.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <returns></returns>
    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    /// <summary>
	/// Generates a random boolean value with a 50% chance of being true or false.
    /// </summary>
    /// <returns></returns>
    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

    /// <summary>
	/// Generates a random vector on the unit circle.
    /// </summary>
    /// <returns></returns>
    inline vec2 onUnitCircle() {
        float angle = getReal(viper::twopi);
        vec2 v;
		v.x = cos(angle);
		v.y = sin(angle);
        return v;
    }
}