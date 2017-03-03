//
//  ServerAPI.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

/*
 Request:
	
 POST	IP_ADDRESS/registration
 BODY    {
 "request" : {
 "login" : <string>,
 "password" : <string>
 }
 }
	Response:
 {
 "method" : "LinBa.registerUser()",
    "response" : {
            ? "ok" : {
                    "dsc" : <string>
                    }
 
            ? "error" : {
                    "dsc" : <string>
                        }
    }
 
 }
 
 јвторизаци€:
 
	Request:
 
 GET IP_ADDRESS/auth/logIn
 PARAMS:
 login=<string>
 password=<string>
 
	Response:
 
 {
 "method" : "LinBa.logIn()",
 "response" : {
 ? "ok" {
 "token" : <string>
 }
 
 ? "error" {
 "dsc" : <string>
 }
 }
 }
 
 LogOut:
 
	Request:
 
 GET IP_ADDRESS/auth/logOut
 PARAMS:
 token=<string>
 
	Response:
 
 {
 "method" : "LinBa.logOut()",
 "response" : {
 ? "ok" {
 "dsc" : <string>
 }
 
 ? "error" {
 "dsc" : <string>
 }
 }
 }
 
 */

import UIKit
import RxSwift

class ServerAPI {
    
    static let sharedInstance = ServerAPI()
    
    private let parser: EntitiesParser
    
    init() {
        self.parser = EntitiesParser()
    }
    
    func createUser(fullName: String, password: String) -> Observable<String?> {
        let params = ["login": fullName, "password": password]
        return (parser.getResponse(uri: "/registration", params: params as Dictionary<String, AnyObject>, method: .post)?.map({ (response) -> String? in
            self.parser.createUser(response: response)
        }))!
    }
    
    
    func logIn(fullName: String, password: String) -> Observable<Bool> {
        let params = ["login": fullName, "password": password]
        var isSuccess: Observable<Bool>? = nil
        let user = parser.getResponse(uri: "/auth/logIn", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> User? in
            self.parser.getUser(name: fullName, response: response)!
        })
        if user != nil {
            isSuccess = (user?.map({ (user) -> Bool in
                return true
            }))!
        }
        return isSuccess!
    }
    
    
    
    func logOut() -> Bool {
        var isLogOutSuccess = false
        let tokenStr = getToken()
        let params = ["token": tokenStr]
        let end = parser.getResponse(uri: "/auth/logOut", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> String? in
            self.parser.logOut(response: response)
        })
        if end != nil {
            isLogOutSuccess = true
        }
        UserDefaults.standard.removeObject(forKey: "token")
        return isLogOutSuccess
    }
    
    func getFilms() -> Observable<[Film]?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr]
        return (parser.getResponse(uri: "/data/films", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> [Film]? in
            self.parser.getFilms(response: response)
        }))!
    }
    
    
    func getActors() -> Observable<[Actor]?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr]
        return (parser.getResponse(uri: "/data/actors/all", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> [Actor]? in
            self.parser.getActors(response: response)
        }))!
    }
    
    func getActorsByFilmId(filmId: Int) -> Observable<[Actor]?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr, "id": filmId] as [String : Any]
        return (parser.getResponse(uri: "/data/actors/all", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> [Actor]? in
            self.parser.getActors(response: response)
        }))!
    }
    
    func getFavoriteFilms() -> Observable<[Film]?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr]
        return (parser.getResponse(uri: "/usr/favorites", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> [Film]? in
            self.parser.getFilms(response: response)
        }))!
    }
    
    func getProducers() -> Observable<[Producer]?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr]
        return (parser.getResponse(uri: "/data/producers/all", params: params as Dictionary<String, AnyObject>, method: .get)?.map({ (response) -> [Producer]? in
            self.parser.getProducers(response: response)
        }))!
    }
    
    func addFilmToFavorites(filmId: Int) -> Observable<String?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr, "filmId": filmId] as [String : Any]
        return (parser.getResponse(uri: "/usr/favorites/add", params: params as Dictionary<String, AnyObject>, method: .post)?.map({ (response) -> String? in
            self.parser.addFilm(response: response)
        }))!
    }
    
    func deleteFilmToFavorites(filmId: Int) -> Observable<String?> {
        let tokenStr = getToken()
        let params = ["token": tokenStr, "filmId": filmId] as [String : Any]
        return (parser.getResponse(uri: "/usr/favorites/delete", params: params as Dictionary<String, AnyObject>, method: .post)?.map({ (response) -> String? in
            self.parser.deleteFilm(response: response)
        }))!
    }
    
    func getToken() -> String {
        var tokenStr: String!
        if let token = UserDefaults.standard.value(forKey: "token") {
            tokenStr = token as! String
        }
        return tokenStr
    }
}
