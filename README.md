# flashrom-add-puya-PY25Q128HA-support

This repository includes the necessary modifications to add support for the Puya PY25Q128HA 128Mbit SPI Flash memory to the `flashrom-master` project. The changes involve updating the `flashchips.c` file with the appropriate definitions and configurations for this specific flash memory chip.


## Definitions and Configuration

To support the Puya PY25Q128HA, you need to add the following definitions to the header files:
```
#define PUYA_ID 0x85
#define PUYA_PY25Q128HA 0x2018
#define FEATURE_4BA_SUPPORT (1 << 3)
```

These define the manufacturer ID, the chip ID, and the support for 4-byte addressing, which is essential for handling the memory correctly.


**Code Addition to flashchips.c**
In the flashchips.c file, the following code block should be added to include support for the Puya PY25Q128HA chip:
```` 
{
		.vendor         = "Puya",
		.name           = "PY25Q128HA",
		.bustype        = BUS_SPI,
		.manufacture_id = PUYA_ID,  // Manufacturer ID 0x85
		.model_id       = PUYA_PY25Q128HA, // Model ID 0x2018
		.total_size     = 16384, // Total size of 128 Mbit = 16 MByte
		.page_size      = 256, // Page size of 256 bytes
		.feature_bits   = FEATURE_WRSR_WREN | FEATURE_4BA_SUPPORT, // Enable Write Status Register and 4-Byte Addressing support
		.tested         = TEST_OK_PREW, // Tested and verified to work
		.block_erasers  = {
			{
				.eraseblocks = { {4 * 1024, 4096 } }, // 4KB block size, 4096 blocks
				.block_erase = SPI_BLOCK_ERASE_20,   // Command 0x20 for 4KB Sector Erase
			}, {
				.eraseblocks = { {32 * 1024, 512 } }, // 32KB block size, 512 blocks
				.block_erase = SPI_BLOCK_ERASE_52,   // Command 0x52 for 32KB Block Erase
			}, {
				.eraseblocks = { {64 * 1024, 256 } }, // 64KB block size, 256 blocks
				.block_erase = SPI_BLOCK_ERASE_D8,   // Command 0xD8 for 64KB Block Erase
			}
		},
   		.printlock = SPI_PRETTYPRINT_STATUS_REGISTER_BP4_SRWD, // Interpret status register to show BP and SRP bits
    	.unlock = SPI_DISABLE_BLOCKPROTECT_BP4_SRWD, // Function to disable block protection by clearing BP bits and handling SRP
		.write          = SPI_CHIP_WRITE256,  // Function to write 256 bytes per page
		.read           = SPI_CHIP_READ,      // Basic function to read data from the chip
		.voltage        = {2700, 3600},        // Operating voltage range: 2.7V-3.6V
	},
````


## Explanation of the Code
Vendor and Name: Specifies that this configuration is for the "Puya" vendor and the "PY25Q128HA" model.

Bus Type: This chip uses the SPI bus (BUS_SPI).

Manufacturer and Model ID: The unique identifiers for the chip (PUYA_ID and PUYA_PY25Q128HA).

## Memory Configuration
total_size: Total memory size of 128Mbit (16MByte).

page_size: Page size of 256 bytes, which is the basic unit of programming.

Feature Bits: Includes write enable and 4-byte addressing support.

Block Erasers: Defines the erase commands for 4KB, 32KB, and 64KB blocks, which are standard for this type of flash memory.

Read and Write Functions: Standard functions used for reading and writing to the chip.

Voltage Range: The operating voltage range for the chip is 2.7V to 3.6V.

Conclusion
These changes enable flashrom to properly interact with the Puya PY25Q128HA chip, allowing for operations such as reading, writing, and erasing flash memory on devices using this chip.

##Additional Notes
Ensure that all necessary headers are correctly included in the flashchips.c file for the definitions and functions used.

Test the modified flashrom thoroughly on a device with the Puya PY25Q128HA chip to ensure all operations work as expected.

This information should help anyone interested in adding support for the Puya PY25Q128HA chip to flashrom.
