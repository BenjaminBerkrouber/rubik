import subprocess
import time
import statistics
import argparse
import os
import csv
import random

import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
DATA_DIR = os.path.join(BASE_DIR, '..', 'data')
CSV_PATH = os.path.abspath(os.path.join(DATA_DIR, 'Kociemba.csv'))

MOVES = [
    "B", "B'", "B2",
    "D", "D'", "D2",
    "F", "F'", "F2",
    "L", "L'", "L2",
    "R", "R'", "R2",
    "U", "U'", "U2"
]

def generate_scramble(length):
    scramble = []
    last_face = ""
    for _ in range(length):
        while True:
            move = random.choice(MOVES)
            face = move[0]
            if face != last_face:
                scramble.append(move)
                last_face = face
                break
    return " ".join(scramble)

def run_benchmark(executable: str, runs: int, scramble_length: int):

    with open(CSV_PATH, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(["time", "spins", "scramble", "solution"])

        for i in range(runs):
            scramble = generate_scramble(scramble_length)
            start = time.perf_counter()
            result = subprocess.run([executable, scramble], capture_output=True, text=True)
            end = time.perf_counter()

            duration = end - start
            output = result.stdout.strip()

            if output == "[KO]":
                writer.writerow([duration, -1, scramble, ""])
                print(f"[{i+1}/{runs}] [KO]")
            else:
                num_spins = len(output.split())
                writer.writerow([duration, num_spins, scramble, output])
                print(f"[{i+1}/{runs}] ✅ {num_spins} spins in {duration:.4f}s")

    print(f"\nResults saved in {CSV_PATH}")

def read_stats():
    if not os.path.exists(CSV_PATH):
        print(f"Fichier introuvable : {CSV_PATH}")
        return

    if os.path.getsize(CSV_PATH) == 0:
        print(f"Fichier vide : {CSV_PATH}")
        return

    times = []
    spins = []
    errors = 0

    with open(CSV_PATH, mode='r') as file:
        reader = csv.DictReader(file)
        rows = list(reader)
        if not rows:
            print(f"Aucune donnée disponible dans {CSV_PATH}")
            return
        for row in rows:
            t = float(row["time"])
            s = int(row["spins"])
            times.append(t)
            if s == -1:
                errors += 1
            else:
                spins.append(s)

    def display(label, data):
        if not data:
            print(f"\n--- {label} ---\nAucune donnée disponible.")
            return
        print(f"\n--- {label} ---")
        print(f"Total       : {len(data)}")
        print(f"Moyenne     : {statistics.mean(data):.4f}")
        print(f"Médiane     : {statistics.median(data):.4f}")
        print(f"Min         : {min(data):.4f}")
        print(f"Max         : {max(data):.4f}")
        print(f"Écart-type  : {statistics.stdev(data):.4f}" if len(data) > 1 else "Écart-type  : N/A")

    display("Temps d'exécution (s)", times)
    display("Nombre de tours", spins)


    print(f"\n[KO] encountered: {errors} / {len(times)} ({(errors / len(times) * 100):.2f}%)")

def main():
    parser = argparse.ArgumentParser(description="Benchmark for the Kociemba solver.")
    parser.add_argument("--run", action="store_true", help="Run tests and write to the CSV file.")
    parser.add_argument("--read", action="store_true", help="Read results from the CSV file.")
    parser.add_argument("-n", "--number", type=int, default=100, help="Number of tests (default: 100)")
    parser.add_argument("--exec", type=str, default="./rubik", help="Path to the executable (default: ./rubik)")
    parser.add_argument("--scramble", type=int, default=25, help="Scramble length (default: 25)")

    args = parser.parse_args()

    if args.run:
        run_benchmark(args.exec, args.number, args.scramble)
    elif args.read:
        read_stats()
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
