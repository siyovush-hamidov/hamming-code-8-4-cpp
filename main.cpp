#include <iostream>
#include "include/HammingCode.h"
#include <bitset>
#include <memory>

int main()
{
    std::unique_ptr<HammingCode> hamming_code = std::make_unique<HammingCode>();
    std::vector<uint8_t> bytes, encoded_bytes, decoded_bytes;
    int choise, block_of_encoded_byte = 1;
    unsigned long long number;
    bool number_is_entered = false, encoded = false;

    while (true)
    {
        std::cout << "ENTER THE OPTION:\n0. ENTER A DECIMAL NUMBER TO WORK WITH\n1. ENCODE\n2. DECODE\n3. MAKE A MISTAKE\n4. EXIT\n";
        std::cin >> choise;

        switch (choise)
        {
        case 0:
            std::cout << "ENTER THE NUMBER: ";
            std::cin >> number;
            number_is_entered = true;
            encoded = false;
            break;

        case 1:
            if (!number_is_entered)
            {
                std::cout << "YOU MUST FIRST USE THE OPTION 0, ENTER THE NUMBER!\nTRY AGAIN.\n";
            }
            else
            {
                bytes = hamming_code->divide_input_number_into_bytes(number);
                encoded_bytes = hamming_code->encode(bytes);
                std::cout << "\nENCODED BYTES:\n";
                for (size_t i = 0; i < bytes.size(); ++i)
                {
                    std::cout << block_of_encoded_byte++ << ". " << std::bitset<4>(bytes[i]) << " IS ENCODED TO " << std::bitset<8>(encoded_bytes[i]) << std::endl;
                }
                std::cout << std::endl;
                block_of_encoded_byte = 0;
                encoded = true;
            }
            break;

        case 2:
            if (encoded)
            {
                decoded_bytes = hamming_code->decode(encoded_bytes);
                if (decoded_bytes.size() > 0)
                {
                    std::cout << "\nDECODED DATA IN BINARY SYSTEM: ";
                    for (uint8_t byte : decoded_bytes)
                        std::cout << std::bitset<4>(byte);
                    std::cout << std::endl;
                }
                else
                {
                    std::cout << "I DON'T KNOW HOW TO DECODE THIS :( ASK CHATGPT." << std::endl;
                }
            }
            else
                std::cout << "YOU HAVE NOT ENCODED ANYTHING! GO AND DO ONE!\n";
            break;

        case 3:
            if (encoded)
            {
                int item_number, byte_number;
                if (encoded_bytes.size() > 1)
                {
                    std::cout << "ENTER THE NUMBER OF THE BYTE (MAX: " << encoded_bytes.size() << "): ";
                    std::cin >> item_number;
                }
                else
                {
                    std::cout << "CAN'T REACH THE ENCODED BYTES!\n" << std::endl;
                    break;
                }

                if (item_number < 1 || item_number > 8)
                {
                    std::cout << "BYTE NUMBER MUST BE GREATER THAN 0 AND LESSER THAN 9!\n" << std::endl;
                    break;
                }

                std::cout << "ENTER THE NUMBER FOR THE BIT: ";
                std::cin >> byte_number;
                if (byte_number >= 1 && byte_number <= 8)
                {
                    int itemIndex = item_number - 1;
                    int bitPosition = byte_number - 1;

                    encoded_bytes[itemIndex] ^= (1 << bitPosition);

                    for (uint8_t byte : encoded_bytes)
                        std::cout << ++block_of_encoded_byte << ". " << std::bitset<8>(byte) << std::endl;

                    std::cout << std::endl;
                    block_of_encoded_byte = 0;
                }
                else
                {
                    std::cout << "BIT NUMBER MUST BE GREATER THAN 0 AND LESSER THAN 9!\n" << std::endl;
                    break;
                }
            }
            else
                std::cout << "YOU HAVE NOT ENCODED ANYTHING! GO AND DO ONE!\n";
            break;

        case 4:
            std::cout << "EXITING PROGRAM...\n";
            return 0;

        default:
            std::cout << "INVALID OPTION, TRY AGAIN!\n";
            break;
        }
    }
    return 0;
}
