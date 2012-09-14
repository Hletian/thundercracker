/*
 * Thundercracker Firmware -- Confidential, not for redistribution.
 * Copyright <c> 2012 Sifteo, Inc. All rights reserved.
 */

/*
 * This is a utility used by the Volume layer.
 *
 * The Erase Log is a special type of Volume, used internally
 * by the Volume layer in order to cache pre-erased blocks and
 * their erase counts.
 *
 * This is a single volume which acts as a very simple FIFO queue
 * for volumes which have been pre-erased during shutdown, and are
 * now available for use in allocating new volumes.
 */

#ifndef FLASH_ERASELOG_H_
#define FLASH_ERASELOG_H_

#include "flash_map.h"
#include "flash_volume.h"

class FlashBlockRecycler;


/**
 * Data storage for information about erased blocks,
 * as a log-structured FIFO within a special volume type.
 */

class FlashEraseLog {
public:
    struct Record {
        uint32_t ec;
        FlashMapBlock block;
        uint8_t flag;
        uint16_t check;
    };

    FlashEraseLog();

    // Record storage
    bool allocate(FlashBlockRecycler &recycler);
    void commit(Record &rec);

    // Record retrieval
    bool pop(Record &rec);

    // Block inventory
    static void clearBlocks(FlashMapBlock::Set &inventory);

    FlashVolume currentVolume() const {
        return volume;
    }

private:
    static const unsigned NUM_RECORDS =
        (FlashMapBlock::BLOCK_SIZE - FlashBlock::BLOCK_SIZE) / sizeof(Record);

    enum RecordFlag {
        F_ERASED = 0xFF,
        F_POPPED = 0x00,
        F_VALID = 0x5F,
    };

    FlashVolume volume;
    unsigned readIndex;
    unsigned writeIndex;

    void findIndices();

    unsigned indexToFlashAddress(unsigned index);
    static uint16_t computeCheck(const Record &r);

    unsigned readFlag(unsigned index);
    void writePopFlag(unsigned index);
    void readRecord(Record &r, unsigned index);
    void writeRecord(Record &r, unsigned index);
};


#endif