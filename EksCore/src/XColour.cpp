#include "XColour"

XColour::XColour()
    {
    }

XColour::XColour( float *in ) : XVector4D( in[0], in[1], in[2], in[3] )
    {
    }

XColour::XColour( double *in ) : XVector4D( in[0], in[1], in[2], in[3] )
    {
    }

XColour::XColour( xReal r, xReal g, xReal b ) : XVector4D( r, g, b, 1.0 )
    {
    }

XColour::XColour( xReal r, xReal g, xReal b, xReal a ) : XVector4D( r, g, b, a )
    {
    }

XColour::XColour( const XVector4D &vec ) : XVector4D( vec.x(), vec.y(), vec.z(), vec.w() )
    {
    }

XColour::XColour( const XLDRColour &col ) : XVector4D( col.redF(), col.greenF(), col.blueF(), col.alphaF() )
    {
    }

XLDRColour XColour::toLDRColour( ) const
    {
    return XLDRColour::fromRgbF( coeff(0), coeff(1), coeff(2), coeff(3) );
    }


XLDRColour operator*( const XLDRColour &a, const XLDRColour &b )
    {
    return XLDRColour( a.red() * b.red(), a.green() * b.green(), a.blue() * b.blue(), a.alpha() * b.alpha() );
    }

XLDRColour operator+( const XLDRColour &a, const XLDRColour &b )
    {
    return XLDRColour( xClamp( a.red() + b.red(), 0, 255 ), xClamp( a.green() + b.green(), 0, 255 ), xClamp( a.blue() + b.blue(), 0, 255 ), xClamp( a.alpha() + b.alpha(), 0, 255 ) );
    }

XLDRColour operator*( xReal a, const XLDRColour &b )
    {
    return XLDRColour::fromRgbF( a * b.redF(), a * b.greenF(), a * b.blueF(), a * b.alphaF() );
    }
