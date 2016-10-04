import QtQuick 2.4
import QtQuick.Window 2.2
import QtMultimedia 5.0

// importar o plugin Urna para comunicação QML/C++
import Urna 1.0

Window {
    visible: true
    width: 800; height: 480
    color: "transparent"

    //declarando o plugin Urna e configurando um id
    //para comunicação com C++
    Urna {
        id: urna
    }

    // timer para exibir a tela final com texto FIM
    Timer {
        id: timer
        interval: 3000; running: false; repeat: false
        onTriggered: {
            showMainWindow()
            timer.running = false
        }
    }

    // funções que alternam entre a tela principal(mainWindow) e a tela final com texto FIM(endVoteScreen)
    function showEndVoteScreen(){
        endVoteScreen.visible = true
        mainWindow.visible = false
        timer.running = true
    }

    function showMainWindow(){
        endVoteScreen.visible = false
        mainWindow.visible = true
    }

    // tela final que exibe texto FIM
    Rectangle {
        id: endVoteScreen
        width: 800;  height: 480
        color: "#f5f5f5"
        visible: false

        Text {
            id: fimText
            text: qsTr("FIM")
            font.pixelSize: 250
            font.family: "Liberation Sans Narrow"
            //font.bold: true
            anchors.centerIn: parent
        }
    }

    // tela principal para entrada de votos
    Rectangle {
        id: mainWindow
        width: 800;  height: 480
        color: "#f5f5f5"

        visible: true

        Rectangle { // pequeno botao touch que exibe informações da urna quando clicado
            id: infoBtn
            width: 35; height: 35
            x:735; y: 20
            visible: true

            Image {
                id: infoBtnImg
                anchors.fill: parent
                source: "sources/info-icon.png"
                visible: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    infoMessage.visible = !infoMessage.visible
                }
            }
        }

        Rectangle { // mensagem que contem versão do software e autor, aparece quando botao info é clicado
            id: infoMessage
            width: 325; height: 50
            x: 250; y: 10
            visible: false
            border.color: "blue"
            radius: 10

            Text {
                text: "    URNA ELETRONICA EDUCATIVA v1.0
  Desenvolvido por: Giovanni Bauermeister"
            }
        }

        Image { // elemento para exibir a imagem dos candidatos
            id: profile
            width: 225; height: 300
            x: 475; y: 60;
            visible: false
        }

        // função que envia para lado C++ o numero digitado e recebe de volta nome, partido e foto do candidato
        // cada 'if' é referente ao tipo de candidato anterior aquele voto ex. se o ultimo voto foi para prefeito,
        //      o software entra com as informações de vereador e vice-cersa
        // essa função é chamada quando se aperta o ultimo digito do candidato, ou seja, ela é chamada no ultimo retangulo
        function updateInfoCandidato() {
            if(tipoCandidato === "prefeito") { //se o voto anterior foi para prefeito
                var numVereador = inputNum1.text + inputNum2.text + inputNum3.text + inputNum4.text
                urna.num_vereador = numVereador
                candidato.text = urna.nome_vereador
                partido.text = urna.partido_vereador
                profile.source = urna.foto_vereador
                profile.visible = true
            }
            if(tipoCandidato === "vereador") { //se o voto anterior foi para vereador
                var numPrefeito = inputNum5.text + inputNum6.text
                urna.num_prefeito = numPrefeito
                candidato.text = urna.nome_prefeito
                partido.text = urna.partido_prefeito
                profile.source = urna.foto_prefeito
                profile.visible = true
            }
        }

        // função que envia o voto para C++ que então salva o voto em arquivo
        // essa função é chamada sempre que se aperta confirma
        function getVote() {
            if(tipoCandidato === "prefeito") { //se o voto anterior foi para prefeito
                var votoVereador = inputNum1.text + inputNum2.text + inputNum3.text + inputNum4.text// + inputNum5.text
                urna.voto_vereador = votoVereador
            }
            if(tipoCandidato === "vereador") { //se o voto anterior foi para vereador
                var votoPrefeito = inputNum5.text + inputNum6.text
                urna.voto_prefeito = votoPrefeito
            }
        }

        // função que limpa e prepara a tela para receber um voto para vereador
        // é chamada quando se aperta corrige ou confirma
        function clearforVereador() {
            cargo.text = "Vereador"

            inputNum1.text = ""
            inputNum2.text = ""
            inputNum3.text = ""
            inputNum4.text = ""

            inputNum5.text = ""
            inputNum6.text = ""

            candidato.text = ""
            partido.text = ""

            inputNum1.enabled = true
            inputNum2.enabled = true
            inputNum3.enabled = true
            inputNum4.enabled = true

            inputNum5.enabled = false
            inputNum6.enabled = false

            num1.visible = true
            num2.visible = true
            num3.visible = true
            num4.visible = true

            num5.visible = false
            num6.visible = false

            lbInstructionsCorrige.visible = false
            lbInstructions.visible = false

            profile.visible = false

            inputNum1.focus = true
            inputNum1.cursorVisible = false
            rec1Animation.running = true
        }

        // função que limpa e prepara a tela para receber um voto para prefeito
        // é chamada quando se aperta corrige ou confirma
        function clearforPrefeito() {
            cargo.text = "Prefeito"

            inputNum1.text = ""
            inputNum2.text = ""
            inputNum3.text = ""
            inputNum4.text = ""

            inputNum5.text = ""
            inputNum6.text = ""

            candidato.text = ""
            partido.text = ""

            inputNum1.enabled = false
            inputNum2.enabled = false
            inputNum3.enabled = false
            inputNum4.enabled = false

            inputNum5.enabled = true
            inputNum6.enabled = true

            num1.visible = false
            num2.visible = false
            num3.visible = false
            num4.visible = false

            num5.visible = true
            num6.visible = true

            lbInstructionsCorrige.visible = false
            lbInstructions.visible = false

            profile.visible = false

            inputNum5.focus = true
            inputNum5.cursorVisible = false
            rec5Animation.running = true
        }

        // aqui se cria os eventos das teclas confirma e corrige
        property var tipoCandidato
        Keys.onPressed: {
            if(event.key == Qt.Key_Backspace) { // se a tecla corrige é pressionada
                if(tipoCandidato === "prefeito") {
                    clearforVereador()
                }
                if(tipoCandidato === "vereador") {
                    clearforPrefeito()
                }

            }
            // se a tecla confirma é presisoana, funciona com enter normal e numerico
            if( (event.key === Qt.Key_Enter || event.key === Qt.Key_Return)  && mainWindow.focus == true) {
                if(candidato.text != "Número inválido"){
                    getVote() // função que envia voto para C++ para ser gravado em arquivo
                    if(tipoCandidato === "vereador") {
                        clearforVereador()
                        showEndVoteScreen()
                    }
                    if(tipoCandidato === "prefeito") {
                        clearforPrefeito()
                    }
                }
            }
        }

        // texto da interface
        Text {
            id: lbTitle
            text: qsTr("SEU VOTO PARA")
            font.family: "Liberation Sans Narrow"
            font.bold: true
            font.wordSpacing: 2
            font.pixelSize: 20
            x: 5; y: 20
        }

        Text { // texto da interface
            id: cargo
            text: qsTr("Vereador")
            font.family: "Liberation Sans Narrow"
            x: 100; y: 80
            font.pixelSize: 50
        }

        Text { // texto da interface
            id: lbNumero
            text: qsTr("Número:")
            font.family: "Liberation Sans Narrow"
            font.pixelSize: 20
            x: 5; y: 215
        }

        Text { // texto da interface
            id: lbNome
            text: qsTr("Nome:")
            font.family: "Liberation Sans Narrow"
            font.pixelSize: 20
            x: 5; y: 310
        }

        Text { // texto que recebe o nome do candidato
            id: candidato
            font.family: "Liberation Sans Narrow"
            font.bold: true
            font.pixelSize: 30
            x: 105; y: 300
        }

        Text { // texto da interface
            id: lbPartido
            text: qsTr("Partido:")
            font.family: "Liberation Sans Narrow"
            font.pixelSize: 20
            x: 5; y: 365
            visible: true
        }

        Text { // texto que recebe o partido
            id: partido
            font.family: "Liberation Sans Narrow"
            font.pixelSize: 25
            x: 105; y: 360
            visible: true
        }

        Rectangle { // linha preta que aparece na parte de baixo da interface
            id: blackline
            width: mainWindow.width; height: 3
            color: "black"
            y: 410
            visible: false
        }

        Text { // texto intrutivo que aparece quando o ultimo numero é digitado
            id: lbInstructions
            text: "Aperte a tecla:" + '\n' + "              VERDE para CONFIRMAR este voto" + '\n' + "          LARANJA para REINICIAR este voto"
            font.family: "Liberation Sans Narrow"
            font.wordSpacing: 2
            font.bold: true
            font.pixelSize: 18
            x: 2; y: 415
            visible: false
        }

        Text { // texto intrutivo que aparece quando o numero é invalido
            id: lbInstructionsCorrige
            text: "Aperte a tecla:" + '\n' + "          LARANJA para REINICIAR este voto"
            font.family: "Liberation Sans Narrow"
            font.wordSpacing: 2
            font.bold: true
            font.pixelSize: 18
            x: 2; y: 415
            visible: false
        }        

        // a partir daqui temos os 6 retangulos onde é digitado o voto.
        // retangulos 1,2,3,4 para vereador e 5,6 para prefeito
        // também pode ser notado a animação de cor das bordas de preto para branco
        Rectangle {
            id: num1

            anchors.left: mainWindow.left
            anchors.leftMargin: 105
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color { // animação da borda do rec1 de preto para branco
                id: rec1Animation
                loops: Animation.Infinite
                running: true

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            // a interface inicia a partir daqui com voto para vereador
            //cada retangulo tem o seu TextInput
            TextInput {
                id: inputNum1
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num1
                focus: true

                onFocusChanged: {
                    blackline.visible = false
                }

                Keys.onPressed: { // aqui pode ser apertado corrige e limpa a tela
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforVereador()
                        rec1Animation.running = true
                    }
                }

                onTextChanged: {
                    inputNum2.focus = true
                    inputNum2.cursorVisible = false
                    rec1Animation.running = false
                    rec2Animation.running = true
                    num1.border.color = "black"
                }
            }
        }

        Rectangle {
            id: num2

            anchors.left: num1.right
            anchors.leftMargin: 10
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color {
                id: rec2Animation
                loops: Animation.Infinite
                running: false

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            TextInput {
                id: inputNum2
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num2
                focus: false

                Keys.onPressed: {
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforVereador()
                        rec2Animation.running = false
                        num2.border.color = "black"
                    }
                }

                onTextChanged: {
                        inputNum3.focus = true
                        inputNum3.cursorVisible = false
                        rec2Animation.running = false
                        rec3Animation.running = true
                        num2.border.color = "black"
                }
            }
        }

        Rectangle {
            id: num3

            anchors.left: num2.right
            anchors.leftMargin: 10
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color {
                id: rec3Animation
                loops: Animation.Infinite
                running: false

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            TextInput {
                id: inputNum3
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num3
                focus: false

                Keys.onPressed: {
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforVereador()
                        rec3Animation.running = false
                        num3.border.color = "black"
                    }
                }

                onTextChanged: {
                    inputNum4.focus = true
                    inputNum4.cursorVisible = false
                    rec3Animation.running = false
                    rec4Animation.running = true
                    num3.border.color = "black"
                }
            }
        }

        Rectangle {
            id: num4

            anchors.left: num3.right
            anchors.leftMargin: 10
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color {
                id: rec4Animation
                loops: Animation.Infinite
                running: false

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            TextInput {
                id: inputNum4
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num4
                focus: false

                Keys.onPressed: {
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforVereador()
                        rec4Animation.running = false
                        num4.border.color = "black"
                    }
                }

                onTextChanged: {
                    inputNum4.focus = false
                    rec4Animation.running = false
                    num4.border.color = "black"
                    blackline.visible = true

                    mainWindow.focus = true                    

                    // troca a variavel tipoCandidato para prefeito, ou seja, o voto para vereador ja foi digitado
                    mainWindow.tipoCandidato = "prefeito"

                    mainWindow.updateInfoCandidato() // coloca as informações do candidato na tela, nome, partido e foto

                    if(candidato.text === "Número inválido") { // checa se o numero é invalido e exibe intruções de acordo
                        lbInstructionsCorrige.visible = true
                        lbInstructions.visible = false
                    }
                    else {
                        lbInstructionsCorrige.visible = false
                        lbInstructions.visible = true
                    }
                }
            }
        }

        // começa retangulo do voto para prefeito
        Rectangle {
            id: num5

            anchors.left: mainWindow.left
            anchors.leftMargin: 105
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            visible: false

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color {
                id: rec5Animation
                loops: Animation.Infinite
                running: false

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            TextInput {
                id: inputNum5
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num5
                focus: false

                onFocusChanged: {
                    blackline.visible = false
                }

                Keys.onPressed: {
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforPrefeito()
                        rec5Animation.running = true
                    }
                }

                onTextChanged: {
                    inputNum6.focus = true
                    inputNum6.cursorVisible = false
                    rec5Animation.running = false
                    rec6Animation.running = true
                    num5.border.color = "black"
                }
            }
        }

        Rectangle {
            id: num6

            anchors.left: num5.right
            anchors.leftMargin: 10
            anchors.verticalCenter: mainWindow.verticalCenter
            anchors.verticalCenterOffset: -10

            visible: false

            width: 60; height: 85

            color: "#f5f5f5"
            border.color: "black"
            border.width: 2

            SequentialAnimation on border.color {
                id: rec6Animation
                loops: Animation.Infinite
                running: false

                ColorAnimation {
                    to: "white"
                    duration: 600
                }

                ColorAnimation {
                    to: "black"
                    duration: 600
                }
            }

            TextInput {
                id: inputNum6
                color: "black"
                font.family: "Latin Modern Mono Prop Light"
                font.pixelSize: 80
                anchors.centerIn: num6
                focus: false

                Keys.onPressed: {
                    if(event.key == Qt.Key_Backspace) {
                        mainWindow.clearforPrefeito()
                        rec6Animation.running = false
                        num6.border.color = "black"
                    }
                }

                onTextChanged: {
                    inputNum6.focus = false
                    rec6Animation.running = false
                    num6.border.color = "black"
                    blackline.visible = true

                    mainWindow.focus = true

                    // troca a variavel tipoCandidato para vereador, ou seja, o voto para prefeito ja foi digitado
                    mainWindow.tipoCandidato = "vereador"

                    mainWindow.updateInfoCandidato() // coloca as informações do candidato na tela, nome, partido e foto

                    if(candidato.text === "Número inválido") { // checa se o numero é invalido e exibe intruções de acordo
                        lbInstructionsCorrige.visible = true
                        lbInstructions.visible = false
                    }
                    else {
                        lbInstructionsCorrige.visible = false
                        lbInstructions.visible = true
                    }
                }
            }
        }
    }
}


