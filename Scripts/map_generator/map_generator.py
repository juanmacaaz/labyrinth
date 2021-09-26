# Generador de mapa

'''
    Ejemplo del ficher mapa.map

    XXXXOXXOX

    XXXXOXOXO
    XOOXOXOXO

    XOXOXOXOO

    XOXOX
    XOXOX

    XOOXOXOXO
    XOXOXX

    Ejemplo de salida:

    vector<vector<vector<char>>> zone = {
    {{'#','#','#','#','O','#','#','O','#'}},
    {{'#','#','#','#','O','#','O','#','O'},{'#','O','O','#','O','#','O','#','O'}},
    {{'#','O','#','O','#','O','#','O','O'}},
    {{'#','O','#','O','#'},{'#','O','#','O','#'}},
    {{'#','O','O','#','O','#','O','#','O'},{'#','O','#','O','#','#'}}};

'''

def generator(file):
    data = open(file).read().split('\n\n')
    data = [x.split('\n') for x in data]

    blocs = 0

    txt = 'vector<vector<vector<int>>> zone = {\n'

    for x in data:
        txt += '{'
        for y in x:
            txt += '{'
            for c in y:
                txt += f"{c},"
                blocs+=1
            txt = txt[:-1] + '},'
        if txt[-1] == ',':
            txt = txt[:-1] + '\n'
        txt = txt[:-1]+'},\n'
    
    txt = txt[:-2] + '};'

    print(f'Se han creado {blocs} bloques.')

    return txt


if __name__ == '__main__':

    gen = generator('mapa.map') 
    print(gen)