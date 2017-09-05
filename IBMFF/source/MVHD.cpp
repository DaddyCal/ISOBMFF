/*******************************************************************************
 * The MIT License (MIT)
 * 
 * Copyright (c) 2017 Jean-David Gadina - www.xs-labs.com / www.imazing.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        MVHD.hpp
 * @copyright   (c) 2017, Jean-David Gadina - www.xs-labs.com / www.imazing.com
 */

#include <IBMFF/MVHD.hpp>

template<>
class XS::PIMPL::Object< IBMFF::MVHD >::IMPL
{
    public:
        
        IMPL( void );
        IMPL( const IMPL & o );
        ~IMPL( void );
        
        uint64_t      _creationTime;
        uint64_t      _modificationTime;
        uint32_t      _timescale;
        uint64_t      _duration;
        uint32_t      _rate;
        uint16_t      _volume;
        uint16_t      _reserved1;
        uint32_t      _reserved2[ 2 ];
        IBMFF::Matrix _matrix;
        uint32_t      _predefined[ 6 ];
        uint32_t      _nextTrackID;
};

#define XS_PIMPL_CLASS IBMFF::MVHD
#include <XS/PIMPL/Object-IMPL.hpp>

namespace IBMFF
{
    MVHD::MVHD( void ): IBMFF::FullBox( "mvhd" )
    {}
    
    void MVHD::ReadData( Parser & parser, BinaryStream & stream )
    {
        FullBox::ReadData( parser, stream );
        
        if( this->GetVersion() == 1 )
        {
            this->SetCreationTime( stream.ReadBigEndianUnsignedLong() );
            this->SetModificationTime( stream.ReadBigEndianUnsignedLong() );
            this->SetTimescale( stream.ReadBigEndianUnsignedInteger() );
            this->SetDuration( stream.ReadBigEndianUnsignedLong() );
        }
        else
        {
            this->SetCreationTime( stream.ReadBigEndianUnsignedInteger() );
            this->SetModificationTime( stream.ReadBigEndianUnsignedInteger() );
            this->SetTimescale( stream.ReadBigEndianUnsignedInteger() );
            this->SetDuration( stream.ReadBigEndianUnsignedInteger() );
        }
        
        this->SetRate( stream.ReadBigEndianUnsignedInteger() );
        this->SetVolume( stream.ReadBigEndianUnsignedShort() );
        
        this->impl->_reserved1      = stream.ReadBigEndianUnsignedShort();
        this->impl->_reserved2[ 0 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_reserved2[ 1 ] = stream.ReadBigEndianUnsignedInteger();
        
        this->SetMatrix( stream.ReadMatrix() );
        
        this->impl->_predefined[ 0 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_predefined[ 1 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_predefined[ 2 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_predefined[ 3 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_predefined[ 4 ] = stream.ReadBigEndianUnsignedInteger();
        this->impl->_predefined[ 5 ] = stream.ReadBigEndianUnsignedInteger();
        
        this->SetNextTrackID( stream.ReadBigEndianUnsignedInteger() );
    }
    
    void MVHD::WriteDescription( std::ostream & os, std::size_t indentLevel ) const
    {
        std::string i( ( indentLevel + 1 ) * 4, ' ' );
        
        FullBox::WriteDescription( os, indentLevel );
        
        os << std::endl
           << i << "- Creation time:     " << this->GetCreationTime() << std::endl
           << i << "- Modification time: " << this->GetModificationTime() << std::endl
           << i << "- Timescale:         " << this->GetTimescale() << std::endl
           << i << "- Duration:          " << this->GetDuration() << std::endl
           << i << "- Rate:              " << this->GetRate() << std::endl
           << i << "- Volume:            " << this->GetVolume() << std::endl
           << i << "- Matrix:            " << this->GetMatrix() << std::endl
           << i << "- Next track ID:     " << this->GetNextTrackID();
    }
    
    uint64_t MVHD::GetCreationTime( void ) const
    {
        return this->impl->_creationTime;
    }
    
    uint64_t MVHD::GetModificationTime( void ) const
    {
        return this->impl->_modificationTime;
    }
    
    uint32_t MVHD::GetTimescale( void ) const
    {
        return this->impl->_timescale;
    }
    
    uint64_t MVHD::GetDuration( void ) const
    {
        return this->impl->_duration;
    }
    
    uint32_t MVHD::GetRate( void ) const
    {
        return this->impl->_rate;
    }
    
    uint16_t MVHD::GetVolume( void ) const
    {
        return this->impl->_volume;
    }
    
    Matrix MVHD::GetMatrix( void ) const
    {
        return this->impl->_matrix;
    }
    
    uint32_t MVHD::GetNextTrackID( void ) const
    {
        return this->impl->_nextTrackID;
    }
    
    void MVHD::SetCreationTime( uint64_t value )
    {
        this->impl->_creationTime = value;
    }
    
    void MVHD::SetModificationTime( uint64_t value )
    {
        this->impl->_modificationTime = value;
    }
    
    void MVHD::SetTimescale( uint32_t value )
    {
        this->impl->_timescale = value;
    }
    
    void MVHD::SetDuration( uint64_t value )
    {
        this->impl->_duration = value;
    }
    
    void MVHD::SetRate( uint32_t value )
    {
        this->impl->_rate = value;
    }
    
    void MVHD::SetVolume( uint16_t value )
    {
        this->impl->_volume = value;
    }
    
    void MVHD::SetMatrix( const Matrix & value )
    {
        this->impl->_matrix = value;
    }
    
    void MVHD::SetNextTrackID( uint32_t value )
    {
        this->impl->_nextTrackID = value;
    }
}

XS::PIMPL::Object< IBMFF::MVHD >::IMPL::IMPL( void ):
    _creationTime( 0 ),
    _modificationTime( 0 ),
    _timescale( 0 ),
    _duration( 0 ),
    _rate( 0 ),
    _volume( 0 ),
    _reserved1( 0 ),
    _reserved2{ 0, 0 },
    _predefined{ 0, 0, 0, 0, 0, 0 },
    _nextTrackID( 0 )
{}

XS::PIMPL::Object< IBMFF::MVHD >::IMPL::IMPL( const IMPL & o ):
    _creationTime( o._creationTime ),
    _modificationTime( o._modificationTime ),
    _timescale( o._timescale ),
    _duration( o._duration ),
    _rate( o._rate ),
    _volume( o._volume ),
    _reserved1( o._reserved1 ),
    _reserved2{ o._reserved2[ 0 ], o._reserved2[ 1 ] },
    _matrix( o._matrix ),
    _predefined{ o._predefined[ 0 ], o._predefined[ 1 ], o._predefined[ 2 ], o._predefined[ 3 ], o._predefined[ 4 ], o._predefined[ 5 ] },
    _nextTrackID( o._nextTrackID )
{}

XS::PIMPL::Object< IBMFF::MVHD >::IMPL::~IMPL( void )
{}

