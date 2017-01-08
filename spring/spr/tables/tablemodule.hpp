#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <thero/assert.hpp>

namespace spr
{
    class TableModule
    {
        public:
            template <typename Table>
            void registerTable()
            {
                TH_ASSERT(mTables.count(typeid(Table)) == 0, "Cannot register already registered table");
                mTables[typeid(Table)] = std::make_shared<Table>();
            }
            template <typename Table>
            Table& t()
            {
                return *std::static_pointer_cast<Table>(mTables.at(typeid(Table)));
            }
            template <typename Table>
            const Table& t() const
            {
                return *std::static_pointer_cast<Table>(mTables.at(typeid(Table)));
            }
        private:
            std::unordered_map<std::type_index, std::shared_ptr<void>> mTables;
    };
}
