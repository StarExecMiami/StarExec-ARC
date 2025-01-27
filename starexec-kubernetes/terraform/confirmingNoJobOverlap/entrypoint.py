import argparse
from time import time

def wasteTime():
    i = 1
    while True:
        i *= 2
        yield i
    

def runJob(timeout):
    print(f"Starting job at {time()}")
    t1 = time()
    for _ in wasteTime():
        if (time() - t1) > timeout:
            break

    print(f"Job completed at {time()}")



if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--timeout", type=int, default=60)
    args = parser.parse_args()

    runJob(args.timeout)
