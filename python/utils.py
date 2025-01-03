"""Misc stuff for making this project work"""
import subprocess
from PIL import Image
import numpy as np


GIT_ROOT = \
    subprocess.check_output("git rev-parse --show-toplevel".split()).rstrip().decode()

def read_pgm(path: str) -> np.array:
    """Reads a pgm image file"""
    return np.array(Image.open(path))
