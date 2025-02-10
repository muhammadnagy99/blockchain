#ifndef IBLOCK_BODY_H
#define IBLOCK_BODY_H

#include <string>
#include <vector>
#include <memory>
#include "data/body_data.h"

class IBlockBody {
public:
    virtual std::string get_merkle_root() const = 0;
    virtual const std::vector<std::unique_ptr<BodyData> >& get_data_entries() const = 0;
    virtual ~IBlockBody() = default;
};

#endif // IBLOCK_BODY_H
