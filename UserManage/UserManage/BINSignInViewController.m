//
//  BINSignInViewController.m
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "BINSignInViewController.h"
#import "BINDatabaseHandler.h"

@interface BINSignInViewController ()

@end

@implementation BINSignInViewController

@synthesize user;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    NSLog(@"Load UserManageSDK successfully");
    self.signButton.enabled = NO;
    [self.usernameTextField becomeFirstResponder];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if([segue.identifier isEqualToString:@"normalSignIn"])
    {
        NSLog(@"send");
        id theSegue = segue.destinationViewController;
        [theSegue setValue:user forKey:@"userDetail"];
    }
}


- (IBAction)signButtonPressed:(UIButton *)sender {
    if(self.usernameTextField.text.length && self.passwordTextField.text.length){
        user = [[BINDatabaseHandler databaseHandler] signin:self.usernameTextField.text withPassword:self.passwordTextField.text];
        if(user){
            if([self.usernameTextField.text isEqual: @"admin"]){
                
                [self performSegueWithIdentifier:@"adminSignIn" sender:self];
            }
            else{
                [self performSegueWithIdentifier:@"normalSignIn" sender:self];

            }
            NSLog(@"登录成功");
        }
        else{
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                            message:@"登录失败！请检查你的用户名和密码是否正确。"
                                                           delegate:nil
                                                  cancelButtonTitle:@"OK"
                                                  otherButtonTitles:nil];
            [alert show];
        }
    }
}

- (IBAction)usernameEditingChanged:(UITextField *)sender
{
    [self checkLoginButtonEnabled];
}

- (IBAction)passwordEditingChanged:(UITextField *)sender
{
    [self checkLoginButtonEnabled];
    
}

- (void)checkLoginButtonEnabled
{
    if(self.usernameTextField.text.length && self.passwordTextField.text.length)
    {
        self.signButton.enabled = YES;
    }
    else
    {
        self.signButton.enabled = NO;
    }
    
}

@end
