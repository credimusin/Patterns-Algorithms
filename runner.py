#!/usr/bin/env python3
import argparse
import os
import subprocess
from pathlib import Path

RUNNERS = {
    ".py": ["python3"],
    ".js": ["node"],
    ".go": ["go", "run"],
    ".php": ["php"],
    ".rs": ["rustc", "{file}", "-o", "{bin}", "&&", "{bin}", "&&", "rm", "{bin}"],
    ".cpp": [
        "g++",
        "-std=c++17",
        "{file}",
        "-o",
        "{bin}",
        "&&",
        "{bin}",
        "&&",
        "rm",
        "{bin}",
    ],
}

LANG_MAP = {
    "python": ".py",
    "javascript": ".js",
    "go": ".go",
    "php": ".php",
    "rust": ".rs",
    "cpp": ".cpp",
}

ROOT_DIRS = [
    "Algorithms",
    "ArchitecturalConcepts",
    "ConcurrencyAsync",
    "EnterprisePatterns",
    "Patterns",
    "RefactoringTechniques",
    "SOLID",
]


def clear_screen():
    os.system("cls" if os.name == "nt" else "clear")


def get_implementations(lang_filter=None):
    tree = {}
    for root_dir in ROOT_DIRS:
        path = Path(root_dir)
        if not path.exists():
            continue

        for file_path in path.rglob("*"):
            if file_path.is_file() and file_path.suffix in RUNNERS:
                if lang_filter and file_path.suffix != LANG_MAP.get(lang_filter):
                    continue

                parts = file_path.parts
                category = parts[0]
                item_name = " / ".join(parts[1:-2])
                lang = parts[-2]

                if category not in tree:
                    tree[category] = {}
                if item_name not in tree[category]:
                    tree[category][item_name] = {}

                tree[category][item_name][lang] = file_path
    return tree


def run_file(file_path):
    suffix = file_path.suffix
    if suffix not in RUNNERS:
        print(f"[-] No configuration to run {suffix}")
        return

    cmd_template = RUNNERS[suffix]

    if "{bin}" in " ".join(cmd_template):
        bin_path = "./temp_bin"
        full_cmd = " ".join(cmd_template).format(file=str(file_path), bin=bin_path)
        print(f"[*] Compiling and running: {file_path}")
        subprocess.run(full_cmd, shell=True)
    else:
        full_cmd = cmd_template + [str(file_path)]
        print(f"[*] Running: {' '.join(full_cmd)}")
        subprocess.run(full_cmd)


def interactive_menu(tree):
    while True:
        clear_screen()
        print("=== Patterns & Algorithms Runner ===")
        categories = sorted(tree.keys())
        for i, cat in enumerate(categories, 1):
            print(f"{i}. {cat}")
        print("q. Exit")

        choice = input("\nSelect category: ").strip().lower()
        if choice == "q":
            clear_screen()
            break

        if not choice.isdigit() or int(choice) > len(categories):
            continue

        category = categories[int(choice) - 1]

        while True:
            clear_screen()
            print(f"=== {category} ===")
            items = sorted(tree[category].keys())
            for i, item in enumerate(items, 1):
                print(f"{i}. {item}")
            print("b. Back")

            choice = input("\nSelect item: ").strip().lower()
            if choice == "b":
                break

            if not choice.isdigit() or int(choice) > len(items):
                continue

            item = items[int(choice) - 1]
            langs = tree[category][item]

            lang_names = sorted(langs.keys())
            if len(lang_names) == 1:
                run_file(langs[lang_names[0]])
                input("\nPress Enter to continue...")
            else:
                while True:
                    clear_screen()
                    print(f"=== {item} ({category}) ===")
                    for i, l in enumerate(lang_names, 1):
                        print(f"{i}. {l}")
                    print("b. Back")

                    choice = input("\nSelect language: ").strip().lower()
                    if choice == "b":
                        break
                    if choice.isdigit() and int(choice) <= len(lang_names):
                        run_file(langs[lang_names[int(choice) - 1]])
                        input("\nPress Enter to continue...")
                        break


def main():
    parser = argparse.ArgumentParser(description="Patterns & Algorithms Runner")
    parser.add_argument(
        "--lang", choices=list(LANG_MAP.keys()), help="Filter by language"
    )
    args = parser.parse_args()

    tree = get_implementations(args.lang)

    if not tree:
        print("[-] No implementations found.")
        return

    try:
        interactive_menu(tree)
    except KeyboardInterrupt:
        print("\nExiting...")


if __name__ == "__main__":
    main()
