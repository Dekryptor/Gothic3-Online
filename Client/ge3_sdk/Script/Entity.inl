#include "Script.h"

template< typename PS >
PS & Entity::AccessPropertySet( void )
{
    return *reinterpret_cast< typename PS::PropertySet * >( this );
}

template< typename PS >
PS const & Entity::GetPropertySet( void ) const
{
    return *reinterpret_cast< typename PS::PropertySet const * >( this );
}

template< typename PSP >
PSP & Entity::AccessPropertySetProperty( void )
{
    return *reinterpret_cast< typename PSP::PropertySetProperty * >( this );
}

template< typename PSP >
PSP const & Entity::GetPropertySetProperty( void ) const
{
    return *reinterpret_cast< typename PSP::PropertySetProperty const * >( this );
}

template< typename PS >
typename PS::EnginePropertySet * Entity::AccessEnginePropertySet( void )
{
    return this->AccessPropertySet< PS >().operator ->();
}

template< typename PS >
typename PS::EnginePropertySet const * Entity::GetEnginePropertySet( void ) const
{
    return this->GetPropertySet< PS >().operator ->();
}
