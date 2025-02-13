#ifndef BODYDATA_H
#define BODYDATA_H

#include <string>

class BodyData
{
public:
    virtual std::string to_string() const = 0;
    // virtual std::unique_ptr<BodyData> clone() const = 0;

    virtual ~BodyData() = default;
};

#endif // BODYDATA_H
