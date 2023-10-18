#include <stdio.h>

// проверка, является ли символ "буквой" или разделителем
int IsLetter(char letter) {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < sizeof(alphabet); i++) {
        if (letter == alphabet[i]) {
            return 1;
        }
    }
    return 0;
}

// считывание ввода пользователя
int GetInput(char str[]) {
    int len = 0;
    char input;
    while ((len < 99) && ((input = getchar()) != '\n')) {
        str[len] = input;
        len++;
    }
    //printf("%d\n", len);
    return len;
}

void RotateWords(char str[], int len) {
    // алгоритм таков: сначала мы получаем строку, например, "a+=bc*d" и движемся по ней,
    // проходя по всем символам. При ситуации, когда последним символом была буква, а
    // текущим является разделитель, счетчик слов увеличивается на 1. Когда счетчик получает
    // значение 2, мы получаем подпоследовательность "a+=bc", в ней мы знаем длину второго
    // слова, длину разделителя и ее длину. Затем мы начинаем переставлять буквы второго слова
    // в начало подпоследовательноси: "a+=bc" -> "a+b=c" -> "ab+=c" -> "ba+=c", затем
    // переходим к следующей букве и т.д., пока не получим "bca+=". После чего проделываем
    // подобную операцию, только вместо букв второго слова двигаем символы разделителя
    // в конец второго слова: "bca+=" -> "bc+a=" -> "bc+=a"
    int separator_len = 0; // длина разделителей в последовательности
    int wc = 0; // счетчик количества слов
    int sec_w_l = 0; // длина второго слова
    int sequence_len = 0; // длина всей подпоследовательности
    char last = str[0]; // последний символ
    char cur; // текущий символ
    int is_words_start = 0; // начался ли ввод слов
    for (int i = 0; i < len; i++) {
        cur = IsLetter(str[i]);
        //printf("%c ", str[i]);
        if (is_words_start == 0) {
            if (cur == 1) {
                is_words_start = 1;
            } else {
                continue;
            }
        }
        if ((last == 1) && (cur == 0)) {
            wc++;
        }
        if ((wc == 2) || ((i == (len - 1)) && (cur == 1))) {
            int idx = i;
            if ((i == (len - 1)) && (cur == 1)) {
                sec_w_l++;
                idx++;
                sequence_len++;
            }
            //printf("DEBUG: i: %d\nseparator_len: %d\nsec_w_l: %d\nsequence_len: %d\nstring: %s\n", i, separator_len, sec_w_l, sequence_len, str);
            // передвигаем второе слово в начало последовательности
            for (int j = 0; j < sec_w_l; j++) {
                for (int k = 0; k < sequence_len - sec_w_l; k++) {
                    char buff = str[idx - sec_w_l + j - k - 1];
                    str[idx - sec_w_l + j - k - 1] = str[idx - sec_w_l + j - k];
                    str[idx - sec_w_l + j - k] = buff;
                }
            }
            // передвигаем разделитель в центр последовательности(между первым и вторым словом)
            int first_word_len = sequence_len - sec_w_l - separator_len;
            for (int j = 0; j < separator_len; j++) {
                for (int k = 0; k < first_word_len; k++) {
                    char buff = str[idx - separator_len + j - k - 1];
                    str[idx - separator_len + j - k - 1] = str[idx - separator_len + j - k];
                    str[idx - separator_len + j - k] = buff;
                }
            }
            wc = 1;
            separator_len = 0;
            sequence_len = first_word_len;
            sec_w_l = 0;
        }
        if (cur == 0) {
            separator_len++;
        } else {
            if (wc == 1) {
                sec_w_l++;
            }
        }
        sequence_len++;

        last = cur;
    }

}

int main() {
    printf("Это программа для циклической перестановки слов.\n"
        "Введите строку(не больше 100 символов): ");
    char a[100];
    int len = GetInput(a);
    RotateWords(a, len);
    printf("Результат: %s\n", a);
    return 0;
}