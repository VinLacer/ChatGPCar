import requests
import json
import serial 

API_KEY = "INSIRA AQUI SUA CHAVE DA API DO CHAT GPT"

headers = {"Authorization": f"Bearer {API_KEY}", "Content-Type": "application/json"}
link = "https://api.openai.com/v1/chat/completions"
id_modelo = "gpt-4o-mini" ## AQUI VC PODE ESCOLHER QUAL CHAT QUER USAR

def send_data_to_arduino(data):
    arduino.write(data.encode('utf-8'))

while True:
  try :
    arduino = serial.Serial('COM5', 9600) # COMUNICAÇÃO SERIAL VERIFICAR EM QUAL "COM" O BLUETOOTH ESTA CONECTADO
    print("Arduino Conectado!!!")
    break
  except OSError as e:
    print(e)
while True:
  print("\nDigite")
  data = input()
  
  if "carrinho" in data: ## SOMENTE DA O CONTEXTO PRO CHAT SE NO INPUT TEM CARRINHO, ASSIM VC PODE FILTRAR QUANDO DESEJA CONTROLAR O CARRINHO
    body = {"model": id_modelo,
          "messages":[{"role":"user",
                      "content": f"AQUI VC DEVE DAR UM CONTEXTO PARA O CHAT GPT, EXPLICANDO PARA ELE AS FUNÇÕES IMPLEMENTADAS NO ARDUINO PARA CONTROLAR O CARRINHO E COMO ELAS FUNCIONAM. {data}."}]}
                      ## SE ATENTE TAMBEM A EXPLICAR PARA O CHAT GPT COMO VC GOSTARIA DE RECEBER OS COMANDOS PARA ENVIAR PARA O ARDUINO
                      ## ISSO TEM Q ESTAR BEM CLARO NO CONTEXTO
                      ## DICA: USE O PROPRIO CHAT PARA AJUDAR O CHAT (MÉTODO ITERATIVO DE INPUT)


    body_mensagem = json.dumps(body)
    requisicao = requests.post(link, headers=headers, data=body_mensagem)
    resposta = requisicao.json()
    resposta_final = resposta['choices'][0]["message"]["content"]
    print("Resposta do CHAT: " + resposta_final)
    send_data_to_arduino(resposta_final)

  else:
    body2 = {"model": id_modelo,
          "messages":[{"role":"user",
                      "content": f"{data}"}]}
    body_mensagem = json.dumps(body2)

    requisicao = requests.post(link, headers=headers, data=body_mensagem)
    resposta = requisicao.json()
    resposta_final = resposta['choices'][0]["message"]["content"]
    print("Resposta do CHAT: " + resposta_final)
