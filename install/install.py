import cpuinfo 

def detect_simd():
    info = cpuinfo.get_cpu_info()
    flags = info.get("flags", [])
    
    return {
        "sse2": "sse2" in flags,
        "sse41": "sse4_1" in flags,
        "avx2": "avx2" in flags,
        "avx512": any(f.startswith("avx512") for f in flags),
    }

def choose_best_simd(simd):
    if simd["avx512"]:
        return "avx512"
    if simd["avx2"]:
        return "avx2"
    if simd["sse41"]:
        return "sse41"
    if simd["sse2"]:
        return "sse2"
    return "scalar"

import subprocess

SIMD_FLAGS = {
    "avx512": "-mavx512f",
    "avx2": "-mavx2",
    "sse41": "-msse4.1",
    "sse2": "-msse2",
    "scalar": ""
}

def build(simd_level):
    flag = SIMD_FLAGS[simd_level]

    cmake_args = [
        "cmake", "-B", "build",
        f"-DDELOREAN_SIMD={simd_level.upper()}",
        f"-DCMAKE_CXX_FLAGS={flag} -O3"
    ]

    subprocess.check_call(cmake_args)
    subprocess.check_call(["cmake", "--build", "build", "-j"])

def main():
    simd = detect_simd()
    best = choose_best_simd(simd)

    print(f"[DeloreanDB] Detected SIMD: {best}")

    build(best)

if __name__ == "__main__":
    main()