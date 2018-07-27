from random import random


COMMAND_TEMPLATE = "{{{0:.4f}, {1:.4f}}},\n"
FILE_NAME        = "torres.geo"

# Tamanho total = TAM ** 2
TAM     = 4
VAL_MAX = 100

if __name__ == "__main__":
    print("struct Point points[] = {\n", end='')
    for i in range(1, TAM + 1):
        for j in range(1, TAM + 1):
            string_linha = COMMAND_TEMPLATE.format(
                round(random() * (VAL_MAX - 1), 0) + 1,
                round(random() * (VAL_MAX - 1), 0) + 1
            )
            print(string_linha, end='')
    print("};\n", end='')

