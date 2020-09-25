#include "impl.h"

void DataBrowser::userLeave(const std::string &userId)
{
    m_dataReaders.erase(userId);
}

bool DataBrowser::getDataType1(const std::string &userId, std::vector<size_t> &returnValues) const
{
    auto function = []( IDataSelector* selector, std::vector<size_t>& returnValues ) -> bool
    {
        return selector->getDataType1( returnValues, 0 );
    };

    return safeCall( userId, [this, &returnValues, function]( const std::unique_ptr<IDataSelector>& selector ) -> bool
        {
            return invokeDataRequest( function, selector, returnValues );
        }
    );
}

bool DataBrowser::getDataType2(std::vector<size_t> &returnValues, const std::string &userId) const
{
    auto function = []( IDataSelector* selector, std::vector<size_t>& returnValues ) -> bool
    {
        return selector->getDataType2( returnValues );
    };

    return safeCall( userId, [this, &returnValues, function]( const std::unique_ptr<IDataSelector>& selector ) -> bool
        {
            return invokeDataRequest( function, selector, returnValues );
        }
    );
}

bool DataBrowser::getDataType3(const std::string &userId, std::vector<std::string> &returnValues) const
{
    auto function = [this]( IDataSelector* selector, std::vector<std::string>& returnValues ) -> bool
    {
        std::deque<size_t> unprocessedResults {};
        bool success { selector->getDataType3( unprocessedResults ) };
        returnValues = process( unprocessedResults );
        return success;
    };

    return safeCall( userId, [this, &returnValues, function]( const std::unique_ptr<IDataSelector>& selector ) -> bool
        {
            return invokeDataRequest( function, selector, returnValues );
        }
    );
}

template<class T>
std::vector<std::string> DataBrowser::process(const T& source) const
{
    std::vector<std::string> results;
    std::transform(source.begin(), source.end(), std::back_inserter(results),
                   [](const size_t& value) { return std::to_string(value); });
    return results;
}
