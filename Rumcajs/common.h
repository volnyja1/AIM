//------------------------------------------------------------------------------
/**
 * \file       common.h
 * \author     Jaroslav Sloup & Petr Felkel
 * \date       2010/03/06
 * \brief      Header file containing declaration of common data structures and functions.
 */
//------------------------------------------------------------------------------
#ifndef __COMMON_H
#define __COMMON_H

#ifdef _WIN32
#include <windows.h>
#include <ctype.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>


#ifndef _WIN32
#define _strdup(x) strdup(x)
#endif

/// Max value of long int
#ifndef MAXLONG
  #define MAXLONG     0x7fffffff
#endif

/// Distance of near clipping plane.
#define  PERSPECTIVE_Z_NEAR   0.1f
/// Distance of far clipping plane.
#define  PERSPECTIVE_Z_FAR  100000.0f

/// Data types (already defined on Windows).
#ifndef _WIN32

  #ifndef BYTE
    #define BYTE unsigned char
  #endif

  #ifndef WORD
    #define WORD unsigned short
  #endif

#endif

/// Coordinates to access vectors components.
#define X 0
#define Y 1
#define Z 2
#define W 3

/// Coordinates to access colors components.
#define R 0
#define G 1
#define B 2
#define A 3

/// Value of PI - M_PI is not defined at some platforms.
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

/// Some useful values.
#define INV_4_M_PI 0.07957747154594767
#define SQRT_2 1.4142135623730951
#define INV_SQRT_2 0.70710678118654746

/// Class containing definition of common math functions.
class CMath {

public:

  /// Minimum function.
  inline static int Min(int a, int b) {
    return (a < b) ? a : b;
  }

  inline static float Min(float a, float b) {
    return (a < b) ? a : b;
  }

  inline static double Min(double a, double b) {
    return (a < b) ? a : b;
  }

  /// Maximum function.
  inline static int Max(int a, int b) {
    return (a > b) ? a : b;
  }

  inline static float Max(float a, float b) {
    return (a > b) ? a : b;
  }

  inline static double Max(double a, double b) {
    return (a > b) ? a : b;
  }

  /// Clamp value by minimum and maximum.
  inline static float Clamp(float value, float min, float max) {
    return ( (value > max) ? max : ( (value < min) ? min : value ) );
  }

  inline static double Clamp(double value, double min, double max) {
    return ( (value > max) ? max : ( (value < min) ? min : value ) );
  }

  inline static int Clamp(int value, int min, int max) {
    return ( (value > max) ? max : ( (value < min) ? min : value ) );
  }

  /// Clamp value by maximum.
  inline static float ClampMax(float value, float max) {
    return ( (value > max) ? max : value );
  }

  inline static int ClampMax(int value, int max) {
    return ( (value > max) ? max : value );
  }
  
  inline static double ClampMax(double value, double max) {
    return ( (value > max) ? max : value );
  }

  /// Clamp value by minimum.
  inline static double ClampMin(double value, double min) {
    return ( (value < min) ? min : value );
  }
  
  inline static float ClampMin(float value, float min) {
    return ( (value < min) ? min : value );
  }
  
  inline static int ClampMin(int value, int min) {
    return ( (value < min) ? min : value );
  }

  /// Sign function.
  inline static int Sign(double value) {
    return ( (value > 0.0) ? 1 : ( (value < 0.0) ? -1 : 0 ) );
  }

  inline static int Sign(float value) {
    return ( (value > 0.0f) ? 1 : ( (value < 0.0f) ? -1 : 0 ) );
  }

  inline static int Sign(int value) {
    return ( (value > 0) ? 1 : ( (value < 0) ? -1 : 0 ) );
  }

 /// Constants for conversion radians <=> degrees.
 static double _deg2rad;
 static double _rad2deg;

};

/// Class used to report various errors and warnings.
class CError {

public:

  /// Class constructor.
  CError() {}

  /// Class destructor.
  ~CError() {}

  /// Prints an error string and terminates the application.
  static void FatalError(char *str) {
    std::cerr << str << std::endl;
    exit(1);
  }

  /// Prints a warning.
  static void Warning(char *str) {
    std::cerr << str << std::endl;
  }

};

#endif // __COMMON_H
