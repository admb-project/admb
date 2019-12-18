import sys

if __name__ == '__main__':
  size = len(sys.argv) - 1
  if size == 0:
    print("Usage: python3 compare_outputs.py file1 ... file(s)")
    sys.exit()

  files = []

  i = 1
  while i <= size:
    f = open(sys.argv[i], 'r')
    files.append(f)
    i += 1

  while True:
    f_lines = []
    for f in files:
      lines = []
      while True:
        pos = f.tell()
        line = f.readline()
        if line == '': 
          break
        elif line.startswith("Example:") and len(lines) > 0:
          f.seek(pos)
          break
        else:
          lines.append(line)

      if len(lines) > 0:
        f_lines.append(lines)

    if len(f_lines) == 0:
      break

    print(f_lines)
