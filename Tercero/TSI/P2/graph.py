#!/usr/bin/env python

import random
import sys
from typing import Tuple


def random_node (num_nodes: int) -> int:
    return (random.randint(1, num_nodes))


def generate_nodes (num_nodes: int) -> Tuple[int, int]:
    n1 = random_node(num_nodes)
    n2 = random_node(num_nodes)

    while n1 == n2:
        n2 = random_node(num_nodes)

    return (n1, n2)


def print_graph (num_nodes: int, num_sides: int) -> None:
    print(f"int: NUM_NODES = {num_nodes};")
    print(f"int: NUM_SIDES = {num_sides};")

    print("array[1..NUM_SIDES,1..2] of int: sides = [|", end="")

    for _ in range(num_sides):
        n1, n2 = generate_nodes(num_nodes)
        print(f" {n1},{n2} |", end="")

    print("];")


def parse_args () -> Tuple[int, int]:
    nodes = int(sys.argv[1]) if len(sys.argv) > 1 else random.randint(0, 100) + 1
    sides = int(sys.argv[2]) if len(sys.argv) > 2 else random.randint(0, 100) + 1

    if len(sys.argv) > 3:
        random.seed(int(sys.argv[3]))

    return (nodes, sides)


def main() -> None:
    nodes, sides = parse_args()
    print_graph(nodes, sides)


if __name__ == "__main__":
    main()
