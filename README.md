[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/fuzVHXUh)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-7f7980b617ed060a017424585567c406b6ee15c891e84e1186181d67ecf80aa0.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=11616262)
# Ativ Programação - Memória Compartilhada
Repositório para atividade de programação memória compartilhada entre processos

## Memória Compartilhada

Crie um código-fonte que utilize fork() e shmget() entre 2 processos (pai e filho). Seu código deve garantir que:

* o processo pai e o processo filho compartilhem uma variável simples (por exemplo, inteiro - valor 1)
* processo pai imprime o valor inicial dessa variável; em seguida, cria o processo filho e espera-o
* o processo filho acessa esta variável, realiza uma operação (por exemplo, adição - valor 2, totalizando 3), modificando o valor; em seguida, o processo filho termina
* o processo pai realiza uma outra operação (por exemplo, multiplicação - valor 4, totalizando 12), modificando novamente o valor, e imprime novamente a variável

Essa lógica de execução deve ser garantida no seu código-fonte em C.

**Trabalho individual.**

Você deve submeter:

- o código fonte do seu programa em C (coloque seu nome e TIA no início do código fonte)
- um PDF com prints de tela mostrando a execução do código.
