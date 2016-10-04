#include <QCoreApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication contaVotos(argc, argv);

    int votosMariana = 0;
    int votosFrederico = 0;
    int votosRebeca = 0;
    int votosRodrigo = 0;
    int votosLucasFelipe = 0;
    int votosYago = 0;

    int votosAnaBeatriz = 0;
    int votosLara = 0;
    int votosIsabeli = 0;
    int votosLucasGomes = 0;
    int votosYuri = 0;
    int votosEvlyn = 0;

    int votosLucasBarbosa = 0;
    int votosLuiz = 0;
    int votosMirela = 0;

    int votosLaura = 0;
    int votosGuilherme = 0;
    int votosMarcos = 0;

    int totalVotosManha = 0;
    int totalVotosTarde = 0;

    QString pathVotosVereador = QDir::currentPath() + "votos_vereador.txt";
    QString pathVotosPrefeito = QDir::currentPath() + "votos_prefeito.txt";

    if( (QString(argv[1]) == pathVotosVereador || QString(argv[1]) == "votos_vereador.txt") &&
            (QString(argv[2]) == pathVotosPrefeito || QString(argv[2]) == "votos_prefeito.txt"))
    {

        QFile votosVereador(argv[1]); //abre arquivo votos_vereador.txt
        votosVereador.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream inVotosVereador(&votosVereador);
        while(!inVotosVereador.atEnd()) {
            QString line = inVotosVereador.readLine();

            if(line == "nome:Mariana numero:1180") ++votosMariana;
            if(line == "nome:Frederico numero:1181") ++votosFrederico;
            if(line == "nome:Rebeca numero:1482") ++votosRebeca;
            if(line == "nome:Rodrigo numero:1483") ++votosRodrigo;
            if(line == "nome:Lucas Felipe numero:1584") ++votosLucasFelipe;
            if(line == "nome:Yago numero:1585") ++votosYago;

            if(line == "nome:Ana Beatriz numero:2180") ++votosAnaBeatriz;
            if(line == "nome:Lara numero:2181") ++votosLara;
            if(line == "nome:Isabeli numero:2282") ++votosIsabeli;
            if(line == "nome:Lucas Gomes numero:2283") ++votosLucasGomes;
            if(line == "nome:Yuri numero:2384") ++votosYuri;
            if(line == "nome:Evlyn numero:2385") ++votosEvlyn;
        }

        QFile votosPrefeito(argv[2]); //abre arquivo votos_prefeito.txt
        votosPrefeito.open(QIODevice::ReadWrite | QIODevice::Text);
        QTextStream inVotosPrefeito(&votosPrefeito);
        while(!inVotosPrefeito.atEnd()) {
            QString line = inVotosPrefeito.readLine();

            if(line == "nome:Lucas Barbosa numero:11") ++votosLucasBarbosa;
            if(line == "nome:Luiz Lauria numero:14") ++votosLuiz;
            if(line == "nome:Mirela numero:15") ++votosMirela;

            if(line == "nome:Laura numero:21") ++votosLaura;
            if(line == "nome:Guilherme numero:22") ++votosGuilherme;
            if(line == "nome:Marcos numero:23") ++votosMarcos;
        }

        totalVotosManha = votosLucasBarbosa + votosLuiz + votosMirela;
        totalVotosTarde = votosLaura + votosGuilherme + votosMarcos;

        qDebug() << endl;

        qDebug() << "             MANHA   ";
        qDebug() << "          ***********" << endl;

        qDebug() << "            PREFEITO";
        qDebug() << "  Candidato    |  " << "nº de votos";
        qDebug() << "---------------|---------------";
        qDebug() << "Lucas Barbosa  |     " << votosLucasBarbosa;
        qDebug() << "Luiz Lauria    |     " << votosLuiz;
        qDebug() << "Mirela         |     " << votosMirela << endl;

        qDebug() << "            VEREADOR";
        qDebug() << "  Candidato    |  " << "nº de votos";
        qDebug() << "---------------|---------------";
        qDebug() << "Mariana        |     " << votosMariana;
        qDebug() << "Frederico      |     " << votosFrederico;
        qDebug() << "Rebeca         |     " << votosRebeca;
        qDebug() << "Rodrigo        |     " << votosRodrigo;
        qDebug() << "Lucas Felipe   |     " << votosLucasFelipe;
        qDebug() << "Yago           |     " << votosYago         << endl;

        qDebug() << "Total votos manha:   " << totalVotosManha << endl;

        qDebug() << endl;

        qDebug() << "             TARDE   ";
        qDebug() << "          ***********" << endl;

        qDebug() << "            PREFEITO";
        qDebug() << "  Candidato    | " << "nº de votos";
        qDebug() << "---------------|--------------";
        qDebug() << "Laura          |     " << votosLaura;
        qDebug() << "Ghilherme      |     " << votosGuilherme;
        qDebug() << "Marcos         |     " << votosMarcos << endl;

        qDebug() << "            VEREADOR";
        qDebug() << "  Candidato    |  " << "nº de votos";
        qDebug() << "---------------|---------------";
        qDebug() << "Ana Beatriz    |     " << votosAnaBeatriz;
        qDebug() << "Lara           |     " << votosLara;
        qDebug() << "Isabeli        |     " << votosIsabeli;
        qDebug() << "Lucas Gomes    |     " << votosLucasGomes;
        qDebug() << "Yuri           |     " << votosYuri;
        qDebug() << "Evlyn          |     " << votosEvlyn << endl;

        qDebug() << "Total votos tarde:   " << totalVotosTarde << endl;

        contaVotos.quit();
    }
    else
    {
        qDebug() << "\n No files given! \n"
                    "please specify 'votos_vereador.txt' and 'votos_prefeito.txt' respectively" << endl;
    }

}
