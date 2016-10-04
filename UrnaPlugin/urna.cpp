#include "urna.h"

Urna::Urna(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

Urna::~Urna()
{
}

// essa função é chamada quando se aperta tecla confirma
// grava os votos de vereador no arquivo votos_vereador.txt
// newVotoVereador recebe o número digitado em ambiente QML
void Urna::setVoto_vereador(const QString &newVotoVereador)
{
    // abre o arquivo de votos para gravação do voto vereador (votos_vereador.txt)
    QFile votos_vereador(filePath_votosVereador);
    if(!votos_vereador.open(QIODevice::WriteOnly | QIODevice::Append)) // modo escrita e acrescentar linha
        return;
    QTextStream resultado_vereador(&votos_vereador);

    // abre o arquivo de baco de candidatos json (candidatos.json)
    QFile myjson(filePath_candidatos);
    myjson.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = myjson.readAll();
    QJsonParseError *err = new QJsonParseError();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonData, err);

    QJsonObject jObj = jDoc.object();

    // procura pelo objeto json vereador
    QJsonValue valVereador = jObj.value("vereador");
    QJsonArray arrVereador = valVereador.toArray();

    // percorre por todo objeto vereador procurando pelos subobjetos nome e numero
    for(int i=0; i<arrVereador.size(); i++){

        QJsonObject jObj2 = arrVereador[i].toObject();

        QJsonValue valNome = jObj2.value("nome");
        QJsonValue valNumero = jObj2.value("numero");

        QString nome = valNome.toString();
        QString numero = valNumero.toString();

        // se o numero recebido do ambiente QML for o mesmo do banco de dados,
        //     salva no arquivo nome:"xxxxx" numero:"xxxx" e sai(break) do loop for
        if(numero == newVotoVereador)
        {
            resultado_vereador << "nome:" << nome << " numero:" << numero << endl ;
            m_voto_vereador = newVotoVereador;
            votos_vereador.close();
            break;
        }
    }
    myjson.close();

    emit voto_vereadorChanged();

    // toca o som curto da urna
    QStringList soundFile;
    soundFile << filePath_somCurto;

    QProcess *playSound = new QProcess;
    playSound->start(soundApp, soundFile);
}

// essa função é chamada quando se aperta tecla confirma
// grava os votos de prefeito no arquivo votos_prefeito.txt
// newVotoPrefeito recebe o número digitado em ambiente QML
void Urna::setVoto_prefeito(const QString &newVotoPrefeito)
{
    // abre o arquivo de votos para gravação do voto prefeito (votos_prefeito.txt)
    QFile votos_prefeito(filePath_votosPrefeito);
    if(!votos_prefeito.open(QIODevice::WriteOnly | QIODevice::Append)) // modo escrita e acrescentar linha
        return;
    QTextStream resultado_prefeito(&votos_prefeito);

    // abre o arquivo de baco de candidatos json (candidatos.json)
    QFile myjson(filePath_candidatos);
    myjson.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = myjson.readAll();
    QJsonParseError *err = new QJsonParseError();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonData, err);

    QJsonObject jObj = jDoc.object();

    // procura pelo objeto json prefeito
    QJsonValue valPrefeito = jObj.value("prefeito");
    QJsonArray arrPrefeito = valPrefeito.toArray();

    // percorre por todo objeto prefeito procurando pelos subobjetos nome e numero
    for(int i=0; i<arrPrefeito.size(); i++){

        QJsonObject jObj2 = arrPrefeito[i].toObject();

        QJsonValue valNome = jObj2.value("nome");
        QJsonValue valNumero = jObj2.value("numero");

        QString nome = valNome.toString();
        QString numero = valNumero.toString();

        // se o numero recebido do ambiente QML for o mesmo do banco de dados,
        //     salva no arquivo nome:"xxxxx" numero:"xxxx" e sai(break) do loop for
        if(numero == newVotoPrefeito)
        {
            resultado_prefeito << "nome:" << nome << " numero:" << numero << endl ;
            m_voto_prefeito = newVotoPrefeito;
            votos_prefeito.close();
            break;
        }
    }
    myjson.close();

    emit voto_prefeitoChanged();

    // toca o som longo da urna
    QStringList soundFile;
    soundFile << filePath_somLongo;

    QProcess *playSound = new QProcess;
    playSound->start(soundApp, soundFile);
}

// essa função é chamada quando se digita o ultimo digito do candidato vereador
// recebe o numero do ambiente QML,
//  procura no banco de candidatos json,
//  e retorna com as informações do candidato nome, numero e foto
// newNumVereador recebe numero digitado em ambiente QML
void Urna::setNum_vereador(const QString &newNumVereador)
{
    // abre o baco de candidatos json
    QFile myjson(filePath_candidatos);
    myjson.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = myjson.readAll();
    QJsonParseError *err = new QJsonParseError();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonData, err);

    QJsonObject jObj = jDoc.object();

    // procura pelo objeto json vereador
    QJsonValue valVereador = jObj.value("vereador");
    QJsonArray arrVereador = valVereador.toArray();

    // percorre por todo objeto e procura pelos subobjetos, nome, numero, partido e foto
    for(int i=0; i<arrVereador.size(); i++){

        QJsonObject jObj2 = arrVereador[i].toObject();

        QJsonValue valNome = jObj2.value("nome");
        QJsonValue valNumero = jObj2.value("numero");
        QJsonValue valPartido = jObj2.value("partido");
        QJsonValue valFoto = jObj2.value("foto");

        QString nome = valNome.toString();
        QString numero = valNumero.toString();
        QString partido = valPartido.toString();
        QString foto = valFoto.toString();

        // se o numero recebido do ambiente QML for o mesmo do banco de dados
        //  muda as variáveis nome, partido e foto e envia para ambiente QML que por sua vez exibe na tela
        if(numero == newNumVereador)
        {
            m_nome_vereador = nome;
            m_partido_vereador = partido;
            m_foto_vereador = foto;
            break;
        }
        else // se o numero for invalido, muda as variaveis de acordo, evia para QML que por sua vez exibe na tela
        {
            m_nome_vereador = "Número inválido";
            m_partido_vereador = "";
            m_foto_vereador = "sources/foto_blank.png";
        }
    }
    myjson.close();

    emit num_vereadorChanged();
}

// essa função é chamada quando se digita o ultimo digito do candidato prefeito
// recebe o numero do ambiente QML,
//  procura no banco de candidatos json,
//  e retorna com as informações do candidato nome, numero e foto
// newNumPrefeito recebe numero digitado em ambiente QML
void Urna::setNum_prefeito(const QString &newNumPrefeito)
{
    // abre o baco de candidatos json
    QFile myjson(filePath_candidatos);
    myjson.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray jsonData = myjson.readAll();
    QJsonParseError *err = new QJsonParseError();
    QJsonDocument jDoc = QJsonDocument::fromJson(jsonData, err);

    QJsonObject jObj = jDoc.object();

    // procura pelo objeto json prefeito
    QJsonValue valPrefeito = jObj.value("prefeito");
    QJsonArray arrPrefeito = valPrefeito.toArray();

    // percorre por todo objeto e procura pelos subobjetos, nome, numero, partido e foto
    for(int i=0; i<arrPrefeito.size(); i++){

        QJsonObject jObj2 = arrPrefeito[i].toObject();

        QJsonValue valNome = jObj2.value("nome");
        QJsonValue valNumero = jObj2.value("numero");
        QJsonValue valPartido = jObj2.value("partido");
        QJsonValue valFoto = jObj2.value("foto");

        QString nome = valNome.toString();
        QString numero = valNumero.toString();
        QString partido = valPartido.toString();
        QString foto = valFoto.toString();

        // se o numero recebido do ambiente QML for o mesmo do banco de dados
        //  muda as variáveis nome, partido e foto e envia para ambiente QML que por sua vez exibe na tela
        if(numero == newNumPrefeito)
        {
            m_nome_prefeito = nome;
            m_partido_prefeito = partido;
            m_foto_prefeito = foto;
            break;
        }
        else // se o numero for invalido, muda as variaveis de acordo, evia para QML que por sua vez exibe na tela
        {
            m_nome_prefeito = "Número inválido";
            m_partido_prefeito = "";
            m_foto_prefeito = "sources/foto_blank.png";
        }
    }
    myjson.close();

    emit num_prefeitoChanged();
}

// funções que retornam as variáveis para ambiente QML
QString Urna::voto_vereador() const
{
    return m_voto_vereador;
}

QString Urna::voto_prefeito() const
{
    return m_voto_prefeito;
}

QString Urna::nome_vereador() const
{
    return m_nome_vereador;
}

QString Urna::nome_prefeito() const
{
    return m_nome_prefeito;
}

QString Urna::partido_vereador() const
{
    return m_partido_vereador;
}

QString Urna::partido_prefeito() const
{
    return m_partido_prefeito;
}

QString Urna::foto_vereador() const
{
    return m_foto_vereador;
}

QString Urna::foto_prefeito() const
{
    return m_foto_prefeito;
}
