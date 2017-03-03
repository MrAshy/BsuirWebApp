//
//  FilmsParser.swift
//  LinBa
//
//  Created by Kirill Baranov on 02.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import ObjectMapper
import RxSwift
import Alamofire

class EntitiesParser {
    
    let URL = "http://192.168.2.121"
    
    func getResponse(uri: String, params: Dictionary<String, AnyObject>, method: HTTPMethod) -> Observable<Dictionary<String, AnyObject>>? {
        return Observable.create{ observer in
            Alamofire.request(self.URL+uri, method: method, parameters: params, encoding: URLEncoding(), headers: nil)
                .responseString(completionHandler:  { (response) in
                    print("\(response.request?.httpBody)")
                    let apiError = self.getApiError(response: response.result.value!)
                    if ((response.error) != nil || apiError != nil) {
                        observer.on(.error(response.error!))
                        observer.on(.error(apiError!))
                    } else {
                        let objectDictionary = self.getResponseObject(response: response.result.value!)
                        observer.on(Event.next(objectDictionary!))
                        observer.on(.completed)
                    }
                })
            
            return Disposables.create()
        }
        
    }
    
    func createUser(response: Dictionary<String, AnyObject>?) -> String? {
        return response?["dsc"] as? String
    }
    
    func getUser(name: String, response: Dictionary<String, AnyObject>?) -> User? {
        let token = response?["token"] as! String
        UserDefaults.standard.set(token, forKey: "token")
        UserDefaults.standard.synchronize()
        return User(name: name, token: token)
    }
    
    func logOut(response: Dictionary<String, AnyObject>?) -> String? {
        return response?["dsc"] as? String
    }

    func getFilms(response: Dictionary<String, AnyObject>?) -> [Film]? {
        return Mapper<Film>().mapArray(JSONArray: response?["films"] as! [[String : Any]])
    }
    
    func getActors(response: Dictionary<String, AnyObject>?) -> [Actor]? {
        return Mapper<Actor>().mapArray(JSONArray: response?["actors"] as! [[String : Any]])
    }
    
    func getProducers(response: Dictionary<String, AnyObject>?) -> [Producer]? {
        return Mapper<Producer>().mapArray(JSONArray: response?["producers"] as! [[String : Any]])
    }
    
    func addFilm(response: Dictionary<String, AnyObject>?) -> String? {
        return response?["dsc"] as? String
    }
    
    func deleteFilm(response: Dictionary<String, AnyObject>?) -> String? {
        return response?["dsc"] as? String
    }
    
    func responseToNSDictionry(response: String) -> NSDictionary? {
        var responseDictionary: NSDictionary? = nil
        let data: Data = response.data(using: String.Encoding.utf8)!
        do {
            responseDictionary = try JSONSerialization.jsonObject(with: data, options: JSONSerialization.ReadingOptions.mutableContainers) as? NSDictionary
        } catch {
            NSLog("Deserialization was failed with = \(data)")
        }
        return responseDictionary
    }
    
    
    func getResponseObject(response: String) -> Dictionary<String, AnyObject>? {
        let object = responseToNSDictionry(response: response)
        var entity: Dictionary<String, AnyObject>? = nil
        if (object != nil) {
            if let ok = (object?.object(forKey: "response") as! NSDictionary).object(forKey: "ok") as! Dictionary<String, AnyObject>? {
                entity = ok
            }
        }
        let method = object?.object(forKey: "method") as? String
        NSLog(method!)
        return entity
    }
        
    func getApiError(response: String) -> APIError? {
        var objectError: APIError? = nil
        let object = responseToNSDictionry(response: response)
        if let error = (object?.object(forKey: "response") as! NSDictionary).object(forKey: "error") {
            objectError = error as? APIError
        }
        return objectError
    }
        

    
}
