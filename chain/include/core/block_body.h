#ifndef BLOCK_BODY_H
#define BLOCK_BODY_H

#include "interfaces/iblock_body.h"
#include <vector>
#include <memory>
#include "data/body_data.h"

class BlockBody : public IBlockBody {
private:
    std::vector<std::unique_ptr<BodyData>> data_entries; 

public:
    BlockBody() = default;

    void add_data(std::unique_ptr<BodyData> data);

    std::vector<std::string> get_data_strings() const;

    std::string get_merkle_root() const ; 

    const std::vector<std::unique_ptr<BodyData>>& get_data_entries() const; 
};

#endif // BLOCK_BODY_H
