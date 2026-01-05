# ЛР7. Вариант 4 (UTF8 + UTF16)
### Подсчитать количество полнотелых (со всеми необходимыми ведущими нулями) двоично-кодированных десятичных чисел
> (BCD = Binary Coded Decimal).

> [!IMPORTANT]
> Сборка: `gcc main.c fsm/fsm.c utf/utf-8.c utf/utf-16.c -o meow.out`
> 
> Запуск: `./meow.out --utf16 < tests/dummy_utf16le.txt`
>
> Для создания тестов использованы команды:
> - UTF-8: `echo -e "test\ncontent" > test_utf8.txt`
> - UTF-16 (LE):  `printf '\xFF\xFE' > test_utf16le.txt; iconv -f UTF-8 -t UTF-16LE test_utf8.txt >> test_utf16le.txt`
> - UTF-16 (BE):  `printf '\xFE\xFF' > test_utf16be.txt; iconv -f UTF-8 -t UTF-16BE test_utf8.txt >> test_utf16be.txt`
>
> 
> Для облегчения жизни был написан конвертер **UTF-8 -> UTF-16**:
> ```
> python tests/utf8_to_converter.py tests/dummy_utf8.txt
> ```

## Код
- [**main.c**](./main.c) – определяет в какой кодировке читать, запускает цикл, который проходит по всем символам (до `EOF`)
- **tests** – каталог с тестами и [конвертером](./tests/utf8_to_converter.py)
- **fsm** – реализация конечного автомата
- **utf**:
  - [utf.h](./utf/utf.h) – ручки для получения символа (int32_t) из определённой кодировки
  - [utf-8.c](./utf/utf-8.c), [utf-16.c](./utf/utf-16.c) – реализация этих ручек +utils
