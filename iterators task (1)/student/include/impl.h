#pragma once
#include <iterator>

template <class Container>
struct accumulator : public std::iterator_traits< typename Container::iterator >
{
    /** @todo Iterator traits*/
    using iterator_category = std::output_iterator_tag;

    /** @todo Constructor with container*/

    accumulator( Container& container ) : result( container )
    {

    }

    /** @todo Copy assignment operator*/
    accumulator& operator=( const Container& rhs )
    {
        result += rhs;
        return *this;
    }

    template<typename T>
    accumulator& operator=( const T& rhs )
    {
        for ( const auto& it : rhs )
        {
            result.push_back( it );
        }
        return *this;
    }

    /** @todo Move assignment operator*/
    accumulator& operator=( Container&& rhs )
    {
        for ( auto& it : rhs )
        {
            result.push_back( std::move( it ) );
        }
        return *this;
    }

    /** @todo Iterator operations */
    accumulator& operator*( )
    {
        // empty since output iterator
        return *this;
    }

    accumulator& operator++( )
    {
        // empty since output iterator
        return *this;
    }

    Container& result;
};

/**
 *  @todo Implement accumulator object creator
 */
template<class Container>
accumulator<Container> make_accumulator(Container& container)
{
    return accumulator<Container>( container );
}
