#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <numeric>

const int MAX_PATTERN_LENGTH = int(1e6) + 10;

bool bitset_add(const std::bitset<MAX_PATTERN_LENGTH>& num1_bs,
    const std::bitset<MAX_PATTERN_LENGTH>& num2_bs,
    std::bitset<MAX_PATTERN_LENGTH>& result_bs,
    int pattern_length) {

    std::bitset<MAX_PATTERN_LENGTH> current_num1 = num1_bs;
    std::bitset<MAX_PATTERN_LENGTH> current_num2 = num2_bs;
    bool overflow = false;

    while (current_num2.any()) {
        std::bitset<MAX_PATTERN_LENGTH> carry = current_num1 & current_num2;
        current_num1 ^= current_num2;
        current_num2 = (carry << 1);
        
        if (current_num2.test(pattern_length)) {
            overflow = true;
            current_num2.reset(pattern_length);
        }
    }
    result_bs = current_num1;
    return overflow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string text_y;
    std::string pattern_x;

    std::cin >> text_y >> pattern_x;

    int text_length = text_y.length();
    int pattern_length = pattern_x.length();

    std::bitset<MAX_PATTERN_LENGTH> pattern_char_positions[26];
    std::bitset<MAX_PATTERN_LENGTH> pattern_char_negated_positions[26];

    for (int i = 0; i < pattern_length; ++i) {
        pattern_char_positions[pattern_x[i] - 'a'][i] = 1;
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < pattern_length; ++j) {
            pattern_char_negated_positions[i][j] = !pattern_char_positions[i][j];
        }
    }

    std::vector<std::bitset<MAX_PATTERN_LENGTH>> states(text_length + 1);

    for (int i = 0; i < pattern_length; ++i) {
        states[0][i] = 1;
    }

    int total_overflows = 0;

    for (int j = 1; j <= text_length; ++j) {
        char current_char = text_y[j - 1];
        int char_code = current_char - 'a';

        std::bitset<MAX_PATTERN_LENGTH> temp1_result;
        std::bitset<MAX_PATTERN_LENGTH> temp2_result;

        bool overflow_occurred = bitset_add(states[j - 1],
            (states[j - 1] & pattern_char_positions[char_code]),
            temp1_result,
            pattern_length);

        temp2_result = states[j - 1] & pattern_char_negated_positions[char_code];

        states[j] = temp1_result | temp2_result;

        if (overflow_occurred) {
            total_overflows++;
        }
    }

    std::cout << total_overflows << std::endl;

    return 0;
}
