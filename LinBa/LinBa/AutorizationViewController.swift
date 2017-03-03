//
//  AutorizationViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class AvtorizationViewController: UIViewController {
    
    @IBOutlet weak var tfFullName: UITextField!
    @IBOutlet weak var tfPassword: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()

    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    @IBAction func enterSignUp(_ sender: UIButton) {
    }
    
    @IBAction func enterSignIn(_ sender: UIButton) {
         (ServerAPI.sharedInstance.logIn(fullName: tfFullName.text!, password: tfPassword.text!)).subscribe(onNext: { (success) in
            
            print("Success")
            ServerAPI.sharedInstance.getFilms().subscribe(onNext: { (films) in
                print("\(films)")
            })
         })
    
        
            //self.navigationController?.pushViewController(favoriteVC, animated: true)
        
    }
    
}
