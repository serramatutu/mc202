# Labs MC202

Labs do vavazin :)

## Comandos
```
make:
    ARGUMENTS:
        TARGET      # o lab de destino. ex: lab02

    clean           # limpa o /bin
    build           # builda o TARGET

    baixar_abertos  # baixa testes abertos para TARGET
    baixar_fechados # baixa testes fechados para TARGET
    testar_abertos  # testa testes abertos para TARGET
    testar_fechados # testa testes fechados para TARGET
    checar_abertos  # checa com valgrind testes abertos para TARGET
    checar_fechados # checa com valgrind testes fechados para TARGET
```
Todos os comandos estão disponíveis como tasks do Visual Studio Code