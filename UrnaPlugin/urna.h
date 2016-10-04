#ifndef URNA_H
#define URNA_H

#include <QQuickItem>
#include <QtCore>

// diretório dos arquivos referentes a urna
// candidatos.json, votos_vereadot.txt, votos_prefeito.txt
#ifdef PLATFORM_YOCTO
#define PATH "/home/root/urna-files"
#endif /*PLATFORM_YOCTO*/

#ifdef PLATFORM_RASPBIAN
#define PATH "/home/pi/urna-files"
#endif /*PLATFORM_YOCTO*/

class Urna : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(Urna)

    // declaração das propriedades que poderão ser usadas em ambiente QML
    Q_PROPERTY(QString tipo_candidato READ tipo_candidato WRITE setTipo_candidato NOTIFY tipo_candidatoChanged)
    Q_PROPERTY(QString voto_vereador READ voto_vereador WRITE setVoto_vereador NOTIFY voto_vereadorChanged)
    Q_PROPERTY(QString voto_prefeito READ voto_prefeito WRITE setVoto_prefeito NOTIFY voto_prefeitoChanged)
    Q_PROPERTY(QString nome_prefeito READ nome_prefeito WRITE setNome_prefeito NOTIFY nome_prefeitoChanged)
    Q_PROPERTY(QString nome_vereador READ nome_vereador WRITE setNome_vereador NOTIFY nome_vereadorChanged)
    Q_PROPERTY(QString partido_prefeito READ partido_prefeito WRITE setPartido_prefeito NOTIFY partido_prefeitoChanged)
    Q_PROPERTY(QString partido_vereador READ partido_vereador WRITE setPartido_vereador NOTIFY partido_vereadorChanged)
    Q_PROPERTY(QString num_vereador READ num_vereador WRITE setNum_vereador NOTIFY num_vereadorChanged)
    Q_PROPERTY(QString num_prefeito READ num_prefeito WRITE setNum_prefeito NOTIFY num_prefeitoChanged)
    Q_PROPERTY(QString foto_vereador READ foto_vereador WRITE setFoto_vereador NOTIFY foto_vereadorChanged)
    Q_PROPERTY(QString foto_prefeito READ foto_prefeito WRITE setFoto_prefeito NOTIFY foto_prefeitoChanged)

public:
    Urna(QQuickItem *parent = 0);
    ~Urna();

    // declaração das funções que serão usadas para receber e enviar variáveis para ambiente QML
    QString tipo_candidato() const;
    void setTipo_candidato(const QString &newCandidato);

    QString voto_vereador() const;
    void setVoto_vereador(const QString &newVotoVereador);

    QString voto_prefeito() const;
    void setVoto_prefeito(const QString &newVotoPrefeito);

    QString nome_vereador() const;
    void setNome_vereador(const QString &newNomeVereador);

    QString nome_prefeito() const;
    void setNome_prefeito(const QString &newNomePrefeito);

    QString partido_vereador() const;
    void setPartido_vereador(const QString &newPartidoVereador);

    QString partido_prefeito() const;
    void setPartido_prefeito(const QString &newPartidoPrefeito);

    QString num_vereador() const;
    void setNum_vereador(const QString &newNumVereador);

    QString num_prefeito() const;
    void setNum_prefeito(const QString &newNumPrefeito);

    QString foto_vereador() const;
    void setFoto_vereador(const QString &newFotoPrefeito);

    QString foto_prefeito() const;
    void setFoto_prefeito(const QString &newFotoVereador);

    // declaração dor arquivos da urna
    QString filePath_candidatos = QDir(PATH).filePath("candidatos.json"); // banco de candidatos json
    QString filePath_votosVereador = QDir(PATH).filePath("votos_vereador.txt"); // votos para vereador
    QString filePath_votosPrefeito = QDir(PATH).filePath("votos_prefeito.txt"); // votos para prefeito
    QString filePath_somCurto = QDir(PATH).filePath("sources/som-curto.wav"); // local do arquivo de som curto
    QString filePath_somLongo = QDir(PATH).filePath("sources/som-longo.wav"); // local do arquivo de som longo
    QString soundApp = QDir("/usr/bin/").filePath("aplay"); // aplicação do sistema para tocar os audios

signals:

    //declaração dos sinais que são emitidos quando as variáveis mudam de valor
    void tipo_candidatoChanged();

    void voto_vereadorChanged();
    void voto_prefeitoChanged();

    void nome_vereadorChanged();
    void nome_prefeitoChanged();

    void partido_vereadorChanged();
    void partido_prefeitoChanged();

    void num_vereadorChanged();
    void num_prefeitoChanged();

    void foto_vereadorChanged();
    void foto_prefeitoChanged();

private:

    // declaração das variáveis que recebem valores para serem enviados para ambiente QML
    QString m_tipo_candidato;
    QString m_voto_vereador;
    QString m_voto_prefeito;

    QString m_nome_vereador;
    QString m_nome_prefeito;

    QString m_partido_vereador;
    QString m_partido_prefeito;

    QString m_num_vereador;
    QString m_num_prefeito;

    QString m_foto_vereador;
    QString m_foto_prefeito;
};

#endif // URNA_H
