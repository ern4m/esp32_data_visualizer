# Processamento de Sinais com ESP32 e sensor KY-037

## Introdução

Este projeto foi realizado como trabalho avaliatório relacionado às disciplinas de _Instrumentação e Processamento Digital de Sinais (PDS)_. Tem como finalidade o desenvolvimento de um estudo de caso e aplicação dos conhecimentos obtidos nessas cadeiras para a criação de um dashboard para a visualização dos dados coletados através de um microcontrolador _esp32_ e um sensor sonoro _KY-037_ sendo a aquisição da ordem de grandeza em decibéis dos sons em um ambiente o objetivo a ser alcançado. Para a disciplina de _Instrumentação_ fora definido como principal atividade a regulagem e coleta dos sensores, junto ao armazenamento dos dados coletados em um banco e a disposição destes dados em uma dashboard. Quanto à parte de _PDS_ fora definido a necessidade da utilização da Transformada de Fourrier, por meio do uso do algoritmo de FFT (Fast Fourrier Transform), para a aquisição do espectro dos dados coletados na frequência de forma a serem definidos os picos coletados e consequentemente os decibéis relativos.

## Requerimentos

1. :green_circle: Definição de escopo:
    * Coleta de amostras de som para medir decibéis do ambiente;
2. :green_circle: Hardware: 
   * ESP32;
   * Sensor KY-037;
3. :yellow_circle: Desenvolvimento do código da ESP:
   * :green_circle: Definição dos módulos necessários: 
      * módulo WIFI utilizando protocolo http;
      * módulo FFT;
      * ...
   * :green_circle: Coleta de dados:
     * Loop delay: 5 microsegundos 
     * Valor de amostras (N): 16;
   * :yellow_circle: Funcionalidades:
     * :yellow_circle: Realizar a função de FFT sobre os dados coletados;
     * :yellow_circle: Envio dos dados coletados;
       * Falta adicionar os dados da FFT no pacote HTTP
4. :yellow_circle: Desenvolvimento do código da Dashboard:
    * :green_circle: Definição dos módulos necessários:
      * Servidor: express + sockets.io
      * Banco de dados: A definir (mongo ou postgresql)
      * Biblioteca de gráficos: Plot.ly JS
    * :yellow_circle: Funcionalidades:
      * :yellow_circle: Servidor:
        * :green_circle: Endpoint para receber dados;
        * :yellow_circle: Inserção dos dados no banco;
        * :yellow_circle: Emissão de novos dados por sockets (comunicação deve ser ativada pelo banco);  
      * :green_circle: Gráfico:
        * Inserir novos dados;
        * Definir janela de visualização do gráfico;
      * :yellow_circle: Banco:
        * :yellow_circle: Definir estrutura de dados a ser utilizada;
        * :yellow_circle: Implementar funcionalidade de trigger quando dados novos forem inseridos;
 
