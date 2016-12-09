file=text8

time ./word2vec -train $file -output vectors.bin -cbow 0 -size 100 -window 8 -negative 12 -hs 0 -sample 1e-4 -threads 20 -binary 1 -save-vocab vocab.bin -iter 12
./distance vectors.bin
