/*
-----------------------------------------------------------------------------
This file is part of NxGraphics, Multimedia Engine.
Author : Stephane Kyles. Developed in Prague, Czech Republic.
		_   __       ______                     __     _            
	   / | / /_  __ / ____/_____ ____ _ ____   / /_   (_)_____ _____
	  /  |/ /| |/_// / __ / ___// __ `// __ \ / __ \ / // ___// ___/
	 / /|  /_>  < / /_/ // /   / /_/ // /_/ // / / // // /__ (__  ) 
	/_/ |_//_/|_| \____//_/    \__,_// .___//_/ /_//_/ \___//____/  
									/_/                             
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef __NXGRAPHICSMATH_H__
#define __NXGRAPHICSMATH_H__

#include "NxPrerequisites.h"
 
namespace Nx
{
	class Radian
	{
		Real mRad;

	public:
		explicit Radian ( Real r=0 ) : mRad(r) {}
		Radian ( const Degree& d );
		Radian& operator = ( const Real& f ) { mRad = f; return *this; }
		Radian& operator = ( const Radian& r ) { mRad = r.mRad; return *this; }
		Radian& operator = ( const Degree& d );

		Real valueDegrees() const; // see bottom of this file
		Real valueRadians() const { return mRad; }
		Real valueAngleUnits() const;

        const Radian& operator + () const { return *this; }
		Radian operator + ( const Radian& r ) const { return Radian ( mRad + r.mRad ); }
		Radian operator + ( const Degree& d ) const;
		Radian& operator += ( const Radian& r ) { mRad += r.mRad; return *this; }
		Radian& operator += ( const Degree& d );
		Radian operator - () const { return Radian(-mRad); }
		Radian operator - ( const Radian& r ) const { return Radian ( mRad - r.mRad ); }
		Radian operator - ( const Degree& d ) const;
		Radian& operator -= ( const Radian& r ) { mRad -= r.mRad; return *this; }
		Radian& operator -= ( const Degree& d );
		Radian operator * ( Real f ) const { return Radian ( mRad * f ); }
        Radian operator * ( const Radian& f ) const { return Radian ( mRad * f.mRad ); }
		Radian& operator *= ( Real f ) { mRad *= f; return *this; }
		Radian operator / ( Real f ) const { return Radian ( mRad / f ); }
		Radian& operator /= ( Real f ) { mRad /= f; return *this; }

		bool operator <  ( const Radian& r ) const { return mRad <  r.mRad; }
		bool operator <= ( const Radian& r ) const { return mRad <= r.mRad; }
		bool operator == ( const Radian& r ) const { return mRad == r.mRad; }
		bool operator != ( const Radian& r ) const { return mRad != r.mRad; }
		bool operator >= ( const Radian& r ) const { return mRad >= r.mRad; }
		bool operator >  ( const Radian& r ) const { return mRad >  r.mRad; }

		inline NxGraphics_Export friend std::ostream& operator <<
			( std::ostream& o, const Radian& v )
		{
			o << "Radian(" << v.valueRadians() << ")";
			return o;
		}
	};

    /** Wrapper class which indicates a given angle value is in Degrees.
    @remarks
        Degree values are interchangeable with Radian values, and conversions
        will be done automatically between them.
    */
	class Degree
	{
		Real mDeg; // if you get an error here - make sure to define/typedef 'Real' first

	public:
		explicit Degree ( Real d=0 ) : mDeg(d) {}
		Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
		Degree& operator = ( const Real& f ) { mDeg = f; return *this; }
		Degree& operator = ( const Degree& d ) { mDeg = d.mDeg; return *this; }
		Degree& operator = ( const Radian& r ) { mDeg = r.valueDegrees(); return *this; }

		Real valueDegrees() const { return mDeg; }
		Real valueRadians() const; // see bottom of this file
		Real valueAngleUnits() const;

		const Degree& operator + () const { return *this; }
		Degree operator + ( const Degree& d ) const { return Degree ( mDeg + d.mDeg ); }
		Degree operator + ( const Radian& r ) const { return Degree ( mDeg + r.valueDegrees() ); }
		Degree& operator += ( const Degree& d ) { mDeg += d.mDeg; return *this; }
		Degree& operator += ( const Radian& r ) { mDeg += r.valueDegrees(); return *this; }
		Degree operator - () const { return Degree(-mDeg); }
		Degree operator - ( const Degree& d ) const { return Degree ( mDeg - d.mDeg ); }
		Degree operator - ( const Radian& r ) const { return Degree ( mDeg - r.valueDegrees() ); }
		Degree& operator -= ( const Degree& d ) { mDeg -= d.mDeg; return *this; }
		Degree& operator -= ( const Radian& r ) { mDeg -= r.valueDegrees(); return *this; }
		Degree operator * ( Real f ) const { return Degree ( mDeg * f ); }
        Degree operator * ( const Degree& f ) const { return Degree ( mDeg * f.mDeg ); }
		Degree& operator *= ( Real f ) { mDeg *= f; return *this; }
		Degree operator / ( Real f ) const { return Degree ( mDeg / f ); }
		Degree& operator /= ( Real f ) { mDeg /= f; return *this; }

		bool operator <  ( const Degree& d ) const { return mDeg <  d.mDeg; }
		bool operator <= ( const Degree& d ) const { return mDeg <= d.mDeg; }
		bool operator == ( const Degree& d ) const { return mDeg == d.mDeg; }
		bool operator != ( const Degree& d ) const { return mDeg != d.mDeg; }
		bool operator >= ( const Degree& d ) const { return mDeg >= d.mDeg; }
		bool operator >  ( const Degree& d ) const { return mDeg >  d.mDeg; }

		inline NxGraphics_Export friend std::ostream& operator <<
			( std::ostream& o, const Degree& v )
		{
			o << "Degree(" << v.valueDegrees() << ")";
			return o;
		}
	};

    /** Wrapper class which identifies a value as the currently default angle 
        type, as defined by Math::setAngleUnit.
    @remarks
        Angle values will be automatically converted between radians and degrees,
        as appropriate.
    */
	class Angle
	{
		Real mAngle;
	public:
		explicit Angle ( Real angle ) : mAngle(angle) {}
		operator Radian() const;
		operator Degree() const;
	};

	// these functions could not be defined within the class definition of class
	// Radian because they required class Degree to be defined
	inline Radian::Radian ( const Degree& d ) : mRad(d.valueRadians()) {
	}
	inline Radian& Radian::operator = ( const Degree& d ) {
		mRad = d.valueRadians(); return *this;
	}
	inline Radian Radian::operator + ( const Degree& d ) const {
		return Radian ( mRad + d.valueRadians() );
	}
	inline Radian& Radian::operator += ( const Degree& d ) {
		mRad += d.valueRadians();
		return *this;
	}
	inline Radian Radian::operator - ( const Degree& d ) const {
		return Radian ( mRad - d.valueRadians() );
	}
	inline Radian& Radian::operator -= ( const Degree& d ) {
		mRad -= d.valueRadians();
		return *this;
	}

    /** Class to provide access to common mathematical functions.
        @remarks
            Most of the maths functions are aliased versions of the C runtime
            library functions. They are aliased here to provide future
            optimisation opportunities, either from faster RTLs or custom
            math approximations.
        @note
            <br>This is based on MgcMath.h from
            <a href="http://www.geometrictools.com/">Wild Magic</a>.
    */
    class NxGraphics_Export Math 
    {
	public:
       /** The angular units used by the API. This functionality is now deprecated in favor
	       of discreet angular unit types ( see Degree and Radian above ). The only place
		   this functionality is actually still used is when parsing files. Search for
		   usage of the Angle class for those instances
       */
       enum AngleUnit
       {
           AU_DEGREE,
           AU_RADIAN
       };


       /** This class is used to provide an external random value provider. 
      */
       class RandomValueProvider
       {
       public:
            virtual ~RandomValueProvider() {}
            /** When called should return a random values in the range of [0,1] */
            virtual Real getRandomUnit() = 0;
       };

    protected:
        /// Angle units used by the api
        static AngleUnit msAngleUnit;

        /// Size of the trig tables as determined by constructor.
        static int mTrigTableSize;

        /// Radian -> index factor value ( mTrigTableSize / 2 * PI )
        static Real mTrigTableFactor;
        static Real* mSinTable;
        static Real* mTanTable;

        /// A random value provider. overriding the default random number generator.
        static RandomValueProvider* mRandProvider;

        /** Private function to build trig tables.
        */
        void buildTrigTables();

        static Real SinTable (Real fValue);
        static Real TanTable (Real fValue);
    public:
        /** Default constructor.
            @param
                trigTableSize Optional parameter to set the size of the
                tables used to implement Sin, Cos, Tan
        */
        Math(unsigned int trigTableSize = 4096);

        /** Default destructor.
        */
        ~Math();

		static inline int IAbs (int iValue) { return ( iValue >= 0 ? iValue : -iValue ); }
		static inline int ICeil (float fValue) { return int(ceil(fValue)); }
		static inline int IFloor (float fValue) { return int(floor(fValue)); }
        static int ISign (int iValue);

        /** Absolute value function
            @param
                fValue The value whose absolute value will be returned.
        */
		static inline Real Abs (Real fValue) { return Real(fabs(fValue)); }

        /** Absolute value function
            @param dValue
                The value, in degrees, whose absolute value will be returned.
         */
		static inline Degree Abs (const Degree& dValue) { return Degree(fabs(dValue.valueDegrees())); }

        /** Absolute value function
            @param rValue
                The value, in radians, whose absolute value will be returned.
         */
        static inline Radian Abs (const Radian& rValue) { return Radian(fabs(rValue.valueRadians())); }

        /** Arc cosine function
            @param fValue
                The value whose arc cosine will be returned.
         */
		static Radian ACos (Real fValue);

        /** Arc sine function
            @param fValue
                The value whose arc sine will be returned.
         */
		static Radian ASin (Real fValue);

        /** Arc tangent function
            @param fValue
                The value whose arc tangent will be returned.
         */
		static inline Radian ATan (Real fValue) { return Radian(atan(fValue)); }

        /** Arc tangent between two values function
            @param fY
                The first value to calculate the arc tangent with.
            @param fX
                The second value to calculate the arc tangent with.
         */
		static inline Radian ATan2 (Real fY, Real fX) { return Radian(atan2(fY,fX)); }

        /** Ceiling function
            Returns the smallest following integer. (example: Ceil(1.1) = 2)

            @param fValue
                The value to round up to the nearest integer.
         */
		static inline Real Ceil (Real fValue) { return Real(ceil(fValue)); }
		static inline bool isNaN(Real f)
		{
			// std::isnan() is C99, not supported by all compilers
			// However NaN always fails this next test, no other number does.
			return f != f;
		}

        /** Cosine function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
        static inline Real Cos (const Radian& fValue, bool useTables = false) {
			return (!useTables) ? Real(cos(fValue.valueRadians())) : SinTable(fValue.valueRadians() + HALF_PI);
		}
        /** Cosine function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
        static inline Real Cos (Real fValue, bool useTables = false) {
			return (!useTables) ? Real(cos(fValue)) : SinTable(fValue + HALF_PI);
		}

		static inline Real Exp (Real fValue) { return Real(exp(fValue)); }

        /** Floor function
            Returns the largest previous integer. (example: Floor(1.9) = 1)
         
            @param fValue
                The value to round down to the nearest integer.
         */
        static inline Real Floor (Real fValue) { return Real(floor(fValue)); }

        static inline Real Loga (Real fValue) { return Real(log(fValue)); }

        /// Stored value of log(2) for frequent use
        static const Real LOG2;

        static inline Real Log2 (Real fValue) { return Real(log(fValue)/LOG2); }

        static inline Real LogN (Real base, Real fValue) { return Real(log(fValue)/log(base)); }

        static inline Real Pow (Real fBase, Real fExponent) { return Real(pow(fBase,fExponent)); }

        static Real Sign (Real fValue);
        static inline Radian Sign ( const Radian& rValue )
        {
            return Radian(Sign(rValue.valueRadians()));
        }
        static inline Degree Sign ( const Degree& dValue )
        {
            return Degree(Sign(dValue.valueDegrees()));
        }

        //Simulate the shader function saturate that clamps a parameter value between 0 and 1
        static inline float saturate(float t) { return (t < 0) ? 0 : ((t > 1) ? 1 : t); }
        static inline double saturate(double t) { return (t < 0) ? 0 : ((t > 1) ? 1 : t); }
        
        //Simulate the shader function lerp which performers linear interpolation
        //given 3 parameters v0, v1 and t the function returns the value of (1 � t)* v0 + t * v1. 
        //where v0 and v1 are matching vector or scalar types and t can be either a scalar or a vector of the same type as a and b.
        template<typename V, typename T> static V lerp(const V& v0, const V& v1, const T& t) { 
            return v0 * (1 - t) + v1 * t; }

        /** Sine function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
        static inline Real Sin (const Radian& fValue, bool useTables = false) {
			return (!useTables) ? Real(sin(fValue.valueRadians())) : SinTable(fValue.valueRadians());
		}
        /** Sine function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
        static inline Real Sin (Real fValue, bool useTables = false) {
			return (!useTables) ? Real(sin(fValue)) : SinTable(fValue);
		}

        /** Squared function.
            @param fValue
                The value to be squared (fValue^2)
        */
		static inline Real Sqr (Real fValue) { return fValue*fValue; }

        /** Square root function.
            @param fValue
                The value whose square root will be calculated.
         */
		static inline Real Sqrt (Real fValue) { return Real(sqrt(fValue)); }

        /** Square root function.
            @param fValue
                The value, in radians, whose square root will be calculated.
            @return
                The square root of the angle in radians.
         */
        static inline Radian Sqrt (const Radian& fValue) { return Radian(sqrt(fValue.valueRadians())); }

        /** Square root function.
            @param fValue
                The value, in degrees, whose square root will be calculated.
            @return
                The square root of the angle in degrees.
         */
        static inline Degree Sqrt (const Degree& fValue) { return Degree(sqrt(fValue.valueDegrees())); }

        /** Inverse square root i.e. 1 / Sqrt(x), good for vector
            normalisation.
            @param fValue
                The value whose inverse square root will be calculated.
        */
		static Real InvSqrt (Real fValue);

        /** Generate a random number of unit length.
            @return
                A random number in the range from [0,1].
        */
        static Real UnitRandom ();

        /** Generate a random number within the range provided.
            @param fLow
                The lower bound of the range.
            @param fHigh
                The upper bound of the range.
            @return
                A random number in the range from [fLow,fHigh].
         */
        static Real RangeRandom (Real fLow, Real fHigh);

        /** Generate a random number in the range [-1,1].
            @return
                A random number in the range from [-1,1].
         */
        static Real SymmetricRandom ();

        static void SetRandomValueProvider(RandomValueProvider* provider);
       
        /** Tangent function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
		static inline Real Tan (const Radian& fValue, bool useTables = false) {
			return (!useTables) ? Real(tan(fValue.valueRadians())) : TanTable(fValue.valueRadians());
		}
        /** Tangent function.
            @param fValue
                Angle in radians
            @param useTables
                If true, uses lookup tables rather than
                calculation - faster but less accurate.
        */
		static inline Real Tan (Real fValue, bool useTables = false) {
			return (!useTables) ? Real(tan(fValue)) : TanTable(fValue);
		}

		static inline Real DegreesToRadians(Real degrees) { return degrees * fDeg2Rad; }
        static inline Real RadiansToDegrees(Real radians) { return radians * fRad2Deg; }

       /** These functions used to set the assumed angle units (radians or degrees) 
            expected when using the Angle type.
       @par
            You can set this directly after creating a new Root, and also before/after resource creation,
            depending on whether you want the change to affect resource files.
       */
       static void setAngleUnit(AngleUnit unit);
       /** Get the unit being used for angles. */
       static AngleUnit getAngleUnit(void);

       /** Convert from the current AngleUnit to radians. */
       static Real AngleUnitsToRadians(Real units);
       /** Convert from radians to the current AngleUnit . */
       static Real RadiansToAngleUnits(Real radians);
       /** Convert from the current AngleUnit to degrees. */
       static Real AngleUnitsToDegrees(Real units);
       /** Convert from degrees to the current AngleUnit. */
       static Real DegreesToAngleUnits(Real degrees);

      
       

        /** Compare 2 reals, using tolerance for inaccuracies.
        */
        static bool RealEqual(Real a, Real b,
            Real tolerance = std::numeric_limits<Real>::epsilon());

        /** Calculates the tangent space vector for a given set of positions / texture coords. */
        static Vector3 calculateTangentSpaceVector(
            const Vector3& position1, const Vector3& position2, const Vector3& position3,
            Real u1, Real v1, Real u2, Real v2, Real u3, Real v3);
 
		/** Generates a value based on the Gaussian (normal) distribution function
			with the given offset and scale parameters.
		*/
		static Real gaussianDistribution(Real x, Real offset = 0.0f, Real scale = 1.0f);

		/** Clamp a value within an inclusive range. */
		template <typename T>
		static T Clamp(T val, T minval, T maxval)
		{
			assert (minval <= maxval && "Invalid clamp range");
			return std::max(std::min(val, maxval), minval);
		}

	 
 



        static const Real POS_INFINITY;
        static const Real NEG_INFINITY;
        static const Real PI;
        static const Real TWO_PI;
        static const Real HALF_PI;
		static const Real fDeg2Rad;
		static const Real fRad2Deg;

    };

	// these functions must be defined down here, because they rely on the
	// angle unit conversion functions in class Math:

	inline Real Radian::valueDegrees() const
	{
		return Math::RadiansToDegrees ( mRad );
	}

	inline Real Radian::valueAngleUnits() const
	{
		return Math::RadiansToAngleUnits ( mRad );
	}

	inline Real Degree::valueRadians() const
	{
		return Math::DegreesToRadians ( mDeg );
	}

	inline Real Degree::valueAngleUnits() const
	{
		return Math::DegreesToAngleUnits ( mDeg );
	}

	inline Angle::operator Radian() const
	{
		return Radian(Math::AngleUnitsToRadians(mAngle));
	}

	inline Angle::operator Degree() const
	{
		return Degree(Math::AngleUnitsToDegrees(mAngle));
	}

	inline Radian operator * ( Real a, const Radian& b )
	{
		return Radian ( a * b.valueRadians() );
	}

	inline Radian operator / ( Real a, const Radian& b )
	{
		return Radian ( a / b.valueRadians() );
	}

	inline Degree operator * ( Real a, const Degree& b )
	{
		return Degree ( a * b.valueDegrees() );
	}

	inline Degree operator / ( Real a, const Degree& b )
	{
		return Degree ( a / b.valueDegrees() );
	}
	/** @} */
	/** @} */

}

//#include "OgreHeaderSuffix.h"

#endif