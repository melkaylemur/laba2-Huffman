# laba2-Huffman

ЧАсть 1.
1) Реализован Марковский источник. Матрица переходных вероятностей для источника использовалась следующая:

0.333011 0.489756 0.0242735 0.0572544 0.0957052 

0.230254 0.615684 0.137249 0.0075654 0.00924821 

0.729672 0.165195 0.0826354 0.00955781 0.0129394 

0.564559 0.364779 0.0357187 0.00172597 0.0332167 

0.691689 0.239095 0.0342993 0.00902935 0.025887 


  Энтропия источника 2,0439
  Размер исходного файла = 1,0 МБ (1 000 000 байт)
  
2) Сжать выход Марковского источника в предположении, что символы получены из дискретного стационарного источника без памяти (файл сжат с помощью кода Хаффмана). Скорость 2, 1328

  Размер полученного файла = 213,1 кБ (213 111 байт)
  
3) Сжать выход Марковского источника, оценив матрицу переходных вероятностей по выходу источника (файл сжат с помощью контекстного кода Хаффмана). Скорость 2,00145

  Размер полученного файла = 189,1 кБ (189 050 байт)
  
4) Сжать выход Марковского источника, используя истинную матрицу переходных вероятностей (файл сжат с помощью контекстного кода Хаффмана).Скорость 2,00145

  Размер полученного файла = 189,1 кБ (189 050 байт)
  
Часть 2.
1) Реализован Марковский источник. Матрица переходных вероятностей для источника использовалась следующая:

0.6 0.1 0.1 0.1 0.1
0 0.85 0.05 0 0.1
0 0 1 0 0
0.01 0.05 0.04 0.9 0
0 0 0 0.1 0.9 

  Энтропия источника 0,0139
  Размер исходного файла = 1,0 МБ (1 000 000 байт)
  
2) Сжать выход Марковского источника в предположении, что символы получены из дискретного стационарного источника без памяти (файл сжат с помощью кода Хаффмана). Скорость 0, 01328

  Размер полученного файла = 125,0 кБ (125 019 байт)
  
3) Сжать выход Марковского источника, оценив матрицу переходных вероятностей по выходу источника (файл сжат с помощью контекстного кода Хаффмана). Скорость 0,01015

  Размер полученного файла = 125,0 кБ (125 002 байта)
  
4) Сжать выход Марковского источника, используя истинную матрицу переходных вероятностей (файл сжат с помощью контекстного кода Хаффмана).Скорость 0,01015

  Размер полученного файла = 125,0 кБ (125 002 байта)
