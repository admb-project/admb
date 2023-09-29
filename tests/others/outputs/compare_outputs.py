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
    list_lines = []
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
        list_lines.append(lines)

    if len(list_lines) == 0:
      break

    #print(list_lines)

    jmax = 0
    for lst in list_lines:
      if len(lst) > jmax: 
        jmax = len(lst) 

    print(list_lines[0][0])
    j = 0
    while j < jmax:
      i = 1
      while i < len(list_lines):
        if list_lines[0][j] != list_lines[i][j]:
          #print(list_lines[0][j])
          #print(list_lines[i][j])
          s1 = list_lines[i][j].split()
          k = 0
          for s0 in list_lines[0][j].split():
            if s0 != s1[k]:
              diff = abs(float(s0) - float(s1[k]))
              if diff > 10e-5:
                print('-------')
                print(s0)
                print(s1[k])
                print(diff)
                print('-------')
            k += 1
        i += 1
      j += 1

    #print(max_len)
