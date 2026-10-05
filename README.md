# shopping-app

[![Build](https://github.com/venu-konda/shopping-app/actions/workflows/build.yml/badge.svg)](https://github.com/venu-konda/shopping-app/actions/workflows/build.yml)

A small console shopping application in C++: add products to a cart, view it,
total the bill, and pay from a built-in bank account with a password check.
It is an object-oriented programming exercise (classes, static and const
members, friend classes, references) with no external dependencies.

## Repository layout

The repository contains two directories, `Online_shopping/` and `shopping/`,
which are **byte-for-byte identical copies** of the same four files. Each
directory holds two versions of the program:

| Version | Entry point | Bank class | Design |
|---|---|---|---|
| v1 | `product.cpp` | `Bank.cpp` | A separate `MENU` class owns a `Product` and a `Bank` and drives the menu. `Bank` holds the `PayBill` logic. |
| v2 | `product1.cpp` | `Bank1.cpp` | `Product` itself owns the menu and `PayBill`; it is declared a `friend` of `Bank` and takes the account by reference. `Bank`'s own `PayBill` is commented out. |

v2 is the later refactor. Both versions compile and behave the same from the
user's point of view.

Each entry point `#include`s its `Bank*.cpp` file directly, so **each version
is built from a single translation unit**. Do not pass the `Bank` file to the
compiler as a second source: it would be compiled twice and the link fails
with duplicate definitions of `Bank::cnt` and `passwordCount`.

## Building

Requirements: `g++` (or any C++11 compiler) on **Linux with glibc**. The code
includes `<stdio_ext.h>` and calls `__fpurge()`, which are glibc extensions,
so it does not build on macOS or Windows without changes.

```sh
cd shopping
g++ product1.cpp -o shop        # v2 (recommended)
g++ product.cpp  -o shop_v1     # v1
```

## Usage

Run the binary in a terminal and follow the menu:

```
1.add to cart   2.view cart  3.total bill  4.PayBill  5.exit
enter your choice::
```

- **1. Add to cart**: prompts for a product name (one word), a quantity and a
  unit price. The cart holds at most 5 items; a sixth attempt prints
  `cart is Full`.
- **2. View cart**: lists name, quantity and price per line, or `empty list`.
- **3. Total bill**: prints the sum of quantity × price over the cart.
- **4. PayBill**: asks for the account password. On success the bill is
  deducted from the balance, `sucessfully paid the bill` and the new balance
  are printed, and the cart is emptied. A wrong password prints
  `incorrect password`; a bill larger than the balance prints
  `insufficient funds`.
- **5. Exit**: terminates the program.

The bank account is hard-coded in the `Bank` constructor: holder `venu`, an
opening balance of 200000, and the password `12345`. There is no persistence;
every run starts from the same state.

## Things to know

- **Interactive input only.** The menu calls `__fpurge(stdin)` before each
  prompt to discard stray input. When standard input is a pipe or a file, that
  call discards the whole buffered input, `cin` reaches end-of-file, and the
  loop repeats the last choice forever. Run the program in a terminal, not
  with redirected input.
- A non-numeric menu choice or quantity leaves `cin` in a failed state and the
  loop repeats as above. Use Ctrl-C to stop it.
- Product names are read with `cin >> string`, so a name with spaces is split
  across the following prompts.
- Prices are `float`, but the total printed by choice 3 is stored in an
  `int`, so a fractional total is shown truncated. In v1 the amount actually
  paid goes through the same `int`; in v2 payment uses the exact `float`.
- `Bank` also has `deposit`, `withdraw`, `transfer` and `print` methods that
  the menu never calls; they are left over from an earlier banking exercise.

## Suggested cleanup

The duplicate directory can be removed with `git rm -r Online_shopping` (or
`shopping`) and the two versions kept side by side, or v1 dropped in favour of
v2. No files have been changed in this commit; only this README, a
`.gitignore` and a license were added.

## License

MIT. See [LICENSE](LICENSE).
