#include "stdafx.h"
#include "SaveData.h"

SaveData* SaveDataV1::VersionUp()
{
    SaveDataV2* newData = new SaveDataV2();

    return newData;
}

SaveData* SaveDataV2::VersionUp()
{
    return nullptr;
}
