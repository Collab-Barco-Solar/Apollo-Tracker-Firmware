# Apollo-Tracker-Firmware
O firmware que é executado dentro dos transmissores e receptores do sistema que acompanha a posição em tempo real das embarcações

Foram desenvolvidos dois métodos de comunicação entre os módulos dos barcos (Emissores) e o módulo de terra (Receptor).
Estes métodos estão separados por pastas, são elas:

Todos enviam juntos:
Nesse método todos os Emissores enviam seus dados obtidos do gps ao mesmo tempo, sendo o Receptor responsável por gerenciar como tratar os dados recebidos.
Dessa forma é comum de ocorrer falta de controle na recepção dos dados, pois o receptor pode receber mais informações de um determinado módulo do que de outro,
ja que não há nenhuma forma de controle aplicada a transmissão.

Módulo Receptor Solicita Um-a-Um:
Nesse método o Receptor envia uma mensagem a cada módulo Emissor (essa mensagem foi definida como sendo o numero da equipe), que irá servir como solicitação de dados.
Sendo assim, o Emissor só irá enviar seus dados de GPS ao receber essa mensagem de solicitação, evitando a falta de controle e sobrecarga de canais de comunicação
entre o Receptor e os Emissores.
Após o Receptor enviar a mensagem de solicitação de dados, ele irá aguardar 3 segundos pela mensagem do Emissor, contendo os dados do GPS. Ao serem recebidos, os dados
são salvos em LOG no cartão SD e publicados via rede em  servidor MQTT para exbição na aplicação de monitoramento. Caso o Receptor não receba nenhuma mensagem como
resposta, automaticamente irá solicitar ao próximo módulo, e assim até atingir o último módulo da fila, num ciclo contínuo.

Módulo Receptor Solicita por Grupos:
Nesse método os módulos emissores são separados por grupos de 10, onde cada grupo recebe um Id. Esse id é utilizador pelo Receptor em terra para solicitar dados aos módulos pertencentes a cada grupo. Assim que cada emissor recebe o id do grupo em que está inserido, ele envia dados ao receptor num determinado tempo coordenado para evitar congestionamento de transmissões, haja visto que o receptor pode tratar apenas os dados recebidos de um emissor por vez.
