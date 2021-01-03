# Apollo-Tracker-Firmware
O firmware que é executado dentro dos transmissores e receptores do sistema que acompanha a posição em tempo real das embarcações

Foi desenvolvido um método de comunicação entre os módulos dos barcos (Emissores) e o módulo de terra (Receptor).

Módulo Receptor Solicita por Grupos:
Nesse método os módulos emissores são separados por grupos, onde cada grupo contém no máximo 10 módulos numerados sequencialmente, e cada grupo recebe um Id. Esse id é utilizador pelo Receptor em terra para solicitar dados aos módulos pertencentes a cada grupo. Assim que cada emissor recebe o id do grupo em que está inserido, ele envia dados ao receptor num determinado tempo coordenado para evitar congestionamento de transmissões, haja visto que o receptor pode tratar apenas os dados recebidos de um emissor por vez.
