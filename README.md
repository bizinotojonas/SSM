# SSM
SSP (Sistema de Sensores Modular) consiste numa aplicação em arduino para programar e prototipar sensores que sejam usados em projetos com setpoint de maneira a ter de recompilar o código menos vezes para fazer ajustes no projeto.
#Funcionamento#
O sistema consiste em duas componentes principais, o núcleo e os módulos de sensores.
  O núcleo contem um botão, um potenciometro, um display lcd 16X2 com comunicação I2C, 2 leds uma saída digital para ser conectada em outro sistema e uma entrada de 5 cabos para o módulo do sensor, sendo elas terra, 5v, leitura do tipo de sensor e saida auxiliar do sensor (caso exista)
  O módulo consiste no sensor a ser lido e na resistência especifica do módulo, que é o meio pelo qual o sistema detecta que tipo de sensor está conectado ao núcleo.
#Uso#
O sistema consiste em conectar ao núcleo um sensor para que tenha seu setpoint configurado e reenviado para outro sistema qualquer como uma saida digital. Para a configuração do setpoint, é utilizado o potenciometro linear e um botão, o potenciometro determina o ponto do setpoint, enquanto o botão, inverte a lógica.
  Exemplo, Detectar quando um cômodo está escuro: Primeiro, o módulo de luminosidade é conectado e, em seguida, no display lcd é indicado na primeira linha qual o sensor conectado e na segunda à direita qual sua leitura, numa escala percentual. À esquerda no display, é   constado o valor do setpoint, o qual pode ser configurado pelo potenciometro. Após isso, conecta-se o cabo de saida do sistema, onde um sinal digital será emitido quando o valor de leitura do sensor seja superior ao do setpoint. Caso seja necessário emitir um sinal quando o valor for inferior ao setpoint, basta clicar no botão do sistema.
#sensores#
No momento, este código contem suporte para 3 sensores, sendo eles o de temperatura, luminosidade e ultrasonico, porém é possivel adicionar mais sensores modificando o código. O sistema possui suporte para sensores analógicos e digitais de até 2 saídas, tal qual o sensor ultrasonico.
Para o acréssimo de sensores ao sistema, basta acessar as 4 ultimas funções do mesmo e adicionar mais um argumento ao if, contendo as informações e calculos necessários para o mesmo.
