#ifndef FLASHCHIPS_H
#define FLASHCHIPS_H

struct flashchip {
    const char *vendor;
    const char *name;
    uint16_t manufacture_id;
    uint16_t model_id;
    uint32_t total_size;
    uint16_t page_size;
    uint16_t feature_bits;
    int tested;
    struct block_eraser {
        struct eraseblock {
            uint32_t size;
            uint32_t count;
        } eraseblocks[2];
        void (*block_erase)(struct flashchip *);
    } block_erasers[2];
    void (*printlock)(struct flashchip *);
    void (*unlock)(struct flashchip *);
    void (*write)(struct flashchip *);
    void (*read)(struct flashchip *);
    uint32_t voltage[2];
};

// PUYA PY25Q128HA 정의 추가
static const struct flashchip flashchips[] = {
    {
        .vendor = "Puya",
        .name = "PY25Q128HA",
        .bustype = BUS_SPI,
        .manufacture_id = PUYA_ID, // 이 값은 0x85로 설정되었습니다.
        .model_id = 0x2018,        // 실제 model_id 값
        .total_size = 16384,       // 128 Mbit = 16 MByte
        .page_size = 256,          // 페이지 크기 256 bytes
        .feature_bits = FEATURE_WRSR_WREN | FEATURE_4BA_SUPPORT,
        .tested = TEST_OK_PREW,
        .block_erasers = {
            {
                .eraseblocks = {{4 * 1024, 4096}}, // 4 KB 크기의 블록 4096개
                .block_erase = spi_block_erase_20,
            },
            {
                .eraseblocks = {{64 * 1024, 256}},  // 64 KB 크기의 블록 256개
                .block_erase = spi_block_erase_d8,
            },
        },
        .printlock = spi_prettyprint_status_register_default,
        .unlock = spi_disable_blockprotect_at25df,
        .write = spi_chip_write_256,
        .read = spi_chip_read,
        .voltage = {2700, 3600},   // 전압 범위 2.7V-3.6V
    },
    // 다른 flashchip 정의들...
};

#endif // FLASHCHIPS_H
