#include <qttpserver>

#include "Actions/RegistrationAction.h"
#include "Actions/AuthorizationAction.h"
#include "Actions/getfilmsaction.h"
#include "Actions/favoritesaction.h"
#include "Actions/getactorsaction.h"
#include "Actions/getproducersaction.h"
#include "Actions/rateaction.h"


int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);

    qttp::HttpServer* server = qttp::HttpServer::getInstance();
    server->initialize();


    std::shared_ptr<qttp::Action> registrationContr(new RegistrationAction());
    std::shared_ptr<qttp::Action> authorizationContr(new AutorizationAction());
    std::shared_ptr<qttp::Action> getFilmsContr(new GetFilmsAction());
    std::shared_ptr<qttp::Action> favoritesContr(new FavoritesAction());
    std::shared_ptr<qttp::Action> getActorsContr(new GetActorsAction());
    std::shared_ptr<qttp::Action> getProducerContr(new GetProducersAction());
    std::shared_ptr<qttp::Action> rateContr(new RateAction());

    server->addAction(registrationContr);
    server->addAction(authorizationContr);
    server->addAction(getFilmsContr);
    server->addAction(favoritesContr);
    server->addAction(getActorsContr);
    server->addAction(getProducerContr);
    server->addAction(rateContr);

    server->registerRoute(registrationContr, qttp::HttpMethod::POST, "/registration");
    server->registerRoute(authorizationContr, qttp::HttpMethod::GET, "/auth/:event");

    server->registerRoute(getFilmsContr, qttp::HttpMethod::GET, "/data/films");
    server->registerRoute(getActorsContr, qttp::HttpMethod::GET, "/data/actors/:event");
    server->registerRoute(getProducerContr, qttp::HttpMethod::GET, "/data/producers/:event");

    server->registerRoute(favoritesContr, qttp::HttpMethod::POST, "/usr/favorites/:event");
    server->registerRoute(favoritesContr, qttp::HttpMethod::GET, "/usr/favorites");
    
    server->registerRoute(rateContr, qttp::HttpMethod::GET, "/usr/rate");
    server->registerRoute(rateContr, qttp::HttpMethod::POST, "/usr/rate");

    server->startServer();
    return app.exec();
}
