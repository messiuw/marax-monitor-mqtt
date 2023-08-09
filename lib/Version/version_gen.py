import sys
import subprocess

print("### VERSION GENERATOR ###")

GIT_HASH = subprocess.check_output(["git", "rev-parse", "HEAD"]).decode("utf-8").strip()
GIT_BRANCH = (
    subprocess.check_output(["git", "branch", "--show-current"]).decode("utf-8").strip()
)

print(f"# GIT_HASH: {GIT_HASH}")
print(f"# GIT_BRANCH: {GIT_BRANCH}")

WORK_PATH = sys.path[0]

print(f"# Create version.hpp in {WORK_PATH}")

with open(WORK_PATH + "/version.hpp", "w", encoding="utf-8") as text_file:
    text_file.write("#ifndef VERSION_H\n#define VERSION_H\n\n")

    text_file.write(f"""const char *APP_VERSION = "{GIT_BRANCH}-{GIT_HASH[:7]}";\n\n""")

    text_file.write("#endif // VERSION_H\n")

print("# Creating done!")
print("### VERSION GENERATOR END ###")
