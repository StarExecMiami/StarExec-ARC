region                      = "us-east-1"
timezone                    = "America/New_York"
efs_enable_lifecycle_policy = true
domain                      = "starexec-arc.net"
prover_image                = "tptpstarexec/eprover:latest"
instance_type               = "t3.small"
desired_nodes               = 1
max_nodes                   = 3 
