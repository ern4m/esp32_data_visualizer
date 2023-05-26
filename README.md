# Processamento de Sinais com ESP32 e sensor KY-037

## Introdução

Este projeto foi realizado como trabalho avaliatório relacionado às disciplinas de _Instrumentação e Processamento Digital de Sinais (PDS)_. Tem como finalidade o desenvolvimento de um estudo de caso e aplicação dos conhecimentos obtidos nessas cadeiras para a criação de um dashboard para a visualização dos dados coletados através de um microcontrolador _esp32_ e um sensor sonoro _KY-037_ sendo a aquisição da ordem de grandeza em decibéis dos sons em um ambiente o objetivo a ser alcançado. Para a disciplina de _Instrumentação_ fora definido como principal atividade a regulagem e coleta dos sensores, junto ao armazenamento dos dados coletados em um banco e a disposição destes dados em uma dashboard. Quanto à parte de _PDS_ fora definido a necessidade da utilização da Transformada de Fourrier, por meio do uso do algoritmo de FFT (Fast Fourrier Transform), para a aquisição do espectro dos dados coletados na frequência de forma a serem definidos os picos coletados e consequentemente os decibéis relativos.

## Requerimentos

1. :heavy_check_mark: Escolher o campo de aplicação no qual será feita a coleta dos dados;
2. Realizar a montagem do hardware necessário (esp32 e sensores) para a realização da coleta de dados;
3. Desenvolver o código que irá definir o comportamento da esp32 na coleta de dados, cumprindo os requisitos listados:
   * Definir os módulos necessários para a comunicação de dados entre a esp32 e o dashboard (módulo WIFI utilizando protocolo http);
   * Quanto à coleta de dados foi definida a taxa de amostragem/coleta dos dados obtidos pelo sensor de áudio (KY-037). Neste quesito, foi definido uma taxa de coleta de 5 milisegundos e o valor de 16 amostras de dados;
   * Com isso