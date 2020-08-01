/****************************************************************************//*
 * Copyright (C) 2020 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef FDM_MAINROTORAD_H
#define FDM_MAINROTORAD_H

////////////////////////////////////////////////////////////////////////////////

#include <fdm/models/fdm_MainRotor.h>

////////////////////////////////////////////////////////////////////////////////

namespace fdm
{

/**
 * @brief Helicopter main rotor model class.
 *
 * This model is based on actuator disc theory.
 *
 * Flapping angle is positive upwards.
 *
 * Coordinate Systems Used for Rotor Calculations
 *
 * Rotor Axis System (RAS)
 * Origin of the Rotor Axis System is coincident with the rotor hub center,
 * the x-axis is positive forwards, the y-axis is positive right and z-axis
 * is positive downwards and coincident with the rotor shaft axis.
 *
 * Rotor-Wind Axis System (RWAS)
 * Rotor-Wind Axis System is very much like Rotor Axis System, the only
 * difference is that it is rotated about z-axis in such a manner that x-axis
 * points directly into relative wind, so there is no lateral airspeed
 * component.
 *
 * Control Axis System (CAS)
 * For most purposes, using the Rotor Axis System causes unnecessary
 * complications. It is convenient to use no cyclic feathering axis system.
 * Origin of the Control Axis System is coincident with the origin of the Rotor
 * Axis System, but it is rotated by angles of the swashplate roll and pitch so
 * there is no cyclic feathering in this coordinate system.
 *
 * Disc Axis System (DAS)
 * Origin of the Disc Axis System is coincident with the origin of the Rotor
 * Axis System, but it is rotated by angles of the rotor cone roll and pitch
 * in such a manner that z?axis is perpendicular to the tip path plane so there
 * is no cyclic flapping in this coordinate system.
 *
 * Control-Wind Axis System (CWAS)
 * Control-Wind Axis System is very much like Control Axis System, the only
 * difference is that it is rotated about z-axis in such a manner that x-axis
 * points directly into relative wind, so there is no lateral airspeed
 * component.
 *
 * XML configuration file format:
 * @code
 * <main_rotor>
 *   <hub_center> { [m] x-coordinate } { [m] y-coordinate } { [m] z-coordinate } </hub_center>
 *   <inclination> { [rad] rotor inclination angle (positive if forward) } </inclination>
 *   <number_of_blades> { number of blades } </number_of_blades>
 *   <blade_mass> { [kg] single blade mass } </blade_mass>
 *   <rotor_radius> { [m] rotor radius } </rotor_radius>
 *   <blade_chord> { [m] blades chord } </blade_chord>
 *   <hinge_offset> { [m] flapping hinge offset } </hinge_offset>
 *   <lift_slope> { [1/rad] blade section lift curve slope } </lift_slope>
 *   <tip_losses> { [-] tip losses coefficient } </tip_losses>
 *   <delta_0> { [-] drag coefficient constant component } </delta_0>
 *   <delta_2> { [-] drag coefficient quadratic component } </delta_2>
 *   <beta_max> { [rad] maximum flapping angle } </beta_max>
 *   <ct_max> { [-] maximum thrust coefficient } </ct_max>
 *   <cq_max> { [-] maximum thrust coefficient } </cq_max>
 *   [<thrust_factor> { [-] thrust scaling factor } </thrust_factor>]
 *   [<torque_factor> { [-] torque scaling factor } </torque_factor>]
 *   [<vel_i_factor> { [-] induced velocity scaling factor } </vel_i_factor>]
 * </main_rotor>
 * @endcode
 *
 * Optional elements: "thrust_factor", "torque_factor", "vel_i_factor"
 *
 * @see Mil M.: Helicopters: Calculation and Design. Volume 1: Aerodynamics, NASA, TM-X-74335, 1967
 * @see Gessow A., Myers G.: Aerodynamics of the Helicopter, 1985
 * @see Bramwell A.: Bramwells Helicopter Dynamics, 2001
 * @see Padfield G.: Helicopter Flight Dynamics, 2007
 * @see Stepniewski W.: Rotary-Wing Aerodynamics. Volume I: Basic Theories of Rotor Aerodynamics, 1984
 * @see Johnson W.: Helicopter Theory, 1980
 */
class FDMEXPORT MainRotorAD : public MainRotor
{
public:

    /** Constructor. */
    MainRotorAD();

    /** Destructor. */
    virtual ~MainRotorAD();

    /**
     * Reads data.
     * @param dataNode XML node
     */
    virtual void readData( XmlNode &dataNode );

    /**
     * Computes force and moment.
     * @param vel_bas     [m/s]     aircraft linear velocity vector expressed in BAS
     * @param omg_bas     [rad/s]   aircraft angular velocity expressed in BAS
     * @param acc_bas     [m/s^2]   aircraft linear acceleration vector expressed in BAS
     * @param eps_bas     [rad/s^2] aircraft angular acceleration vector expressed in BAS
     * @param vel_air_bas [m/s]     aircraft linear velocity relative to the air expressed in BAS
     * @param omg_air_bas [rad/s]   aircraft angular velocity relative to the air expressed in BAS
     * @param grav_bas    [m/s^2]   gravity acceleration vector expressed in BAS
     * @param airDensity  [kg/m^3]  air density
     */
    virtual void computeForceAndMoment( const Vector3 &vel_bas,
                                        const Vector3 &omg_bas,
                                        const Vector3 &acc_bas,
                                        const Vector3 &eps_bas,
                                        const Vector3 &vel_air_bas,
                                        const Vector3 &omg_air_bas,
                                        const Vector3 &grav_bas,
                                        double airDensity );

    /**
     * Returns rotor total inartia about shaft axis.
     * @return [kg*m^2] rotor total inartia about shaft axis
     */
    inline double getInertia() const { return _nb * _ib; }

protected:

    Matrix3x3 _ras2cas;         ///< matrix of rotation from RAS to CAS
    Matrix3x3 _cas2ras;         ///< matrix of rotation from CAS to RAS

    Matrix3x3 _bas2cas;         ///< matrix of rotation from BAS to CAS

    Matrix3x3 _bas2das;         ///< matrix of rotation from BAS to DAS
    Matrix3x3 _das2bas;         ///< matrix of rotation from DAS to BAS

    Matrix3x3 _ras2rwas;        ///< matrix of rotation from RAS to RWAS
    Matrix3x3 _rwas2ras;

    Matrix3x3 _cas2cwas;        ///< matrix of rotation from CAS to CWAS
    Matrix3x3 _cwas2cas;        ///< matrix of rotation from CWAS to CAS

    Matrix3x3 _bas2cwas;        ///< matrix of rotation from BAS to CWAS

    int _nb;                    ///< number of rotor blades

    double _r;                  ///< [m] rotor radius
    double _c;                  ///< [m] blades chord
    double _e;                  ///< [m] flapping hinge offset

    double _a;                  ///< [1/rad] blade section lift curve slope
    double _b;                  ///< [-] tip losses coefficient

    double _delta_0;            ///< [-] drag coefficient constant component
    double _delta_2;            ///< [-] drag coefficient quadratic component

    double _beta_max;           ///< [rad] maximum flapping angle

    double _ct_max;             ///< [-] maximum thrust coefficient
    double _cq_max;             ///< [-] maximum torque coefficient

    double _thrust_factor;      ///< [-] thrust scaling factor
    double _torque_factor;      ///< [-] torque scaling factor
    double _vel_i_factor;       ///< [-] induced velocity scaling factor

    double _r2;                 ///< [m^2] rotor radius squared
    double _r3;                 ///< [m^3] rotor radius cubed
    double _r4;                 ///< [m^3] rotor radius to the power of 4
    double _b2;                 ///< [-] tip losses coefficient squared
    double _b3;                 ///< [-] tip losses coefficient cubed
    double _b4;                 ///< [-] tip losses coefficient to the power of 4
    double _ad;                 ///< [m^2] rotor disk area
    double _s;                  ///< [-] rotor solidity

    double _sb;                 ///< [kg*m] single rotor blade first moment of mass about flapping hinge
    double _ib;                 ///< [kg*m^2] single rotor blade inertia moment about flapping hinge
};

} // end of fdm namespace

////////////////////////////////////////////////////////////////////////////////

#endif // FDM_MAINROTORAD_H
