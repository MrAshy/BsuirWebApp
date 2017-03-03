//
//  RegistrationViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class RegistrationViewController: UIViewController {

    
    @IBOutlet weak var tfFullname: UITextField!
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
        ServerAPI.sharedInstance.createUser(fullName: tfFullname.text!, password: tfPassword.text!).subscribe(onNext: { (token) in
            print(token)
        })
    }
        
    
    
    @IBAction func enterCancel(_ sender: UIButton) {
    }
    
}
