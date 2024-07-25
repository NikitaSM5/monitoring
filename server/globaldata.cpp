#include "globaldata.h"

GlobalData::GlobalData() {}

GlobalData *GlobalData::instance()
{
    static GlobalData ret;
    return &ret;
}

GlobalData::~GlobalData() {}
